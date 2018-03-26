/* logger.cpp
****************************************************************************************************************
****************************************************************************************************************

    Copyright (C) 2017, 2018 Askar Almatov

    This file is part of Libiclass. 
    
    Libiclass is free software: you can redistribute it and/or modify it under the terms of the GNU General
    Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.
    
    Libiclass is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
    License for more details.
    
    You should have received a copy of the GNU General Public License along with Libiclass. If not, see
    <http://www.gnu.org/licenses/>.
*/

#include "logger.h"

using namespace iclass;

const unsigned  SLEEP_INTERVAL_     ( 20 );         // milliseconds
const unsigned  FLUSH_INTERVAL_     ( 200 );        // milliseconds
const unsigned  WRITE_BUFFER_SIZE_  ( 512 );        // bytes

/**************************************************************************************************************/
LoggerQueue::LoggerQueue( unsigned ringSize ) :
    ringSize_( ringSize ),
    overflows_a_( 0 )
{
    ring_c_ = new uint8_t[ ringSize_ ];
    front_c_ = ring_c_;
    back_c_ = ring_c_;
}

/**************************************************************************************************************/
LoggerQueue::~LoggerQueue()
{
    this->lock();

    delete[] ring_c_;
}

/**************************************************************************************************************/
unsigned
LoggerQueue::pull( uint8_t* buffer, unsigned bufferSize, bool& isExhausted )
{
    unsigned  nBytes( 0 );

    this->lock();

    if ( front_c_ != back_c_ )
    {
        if ( front_c_ > back_c_ )
        {
            nBytes = front_c_ - back_c_;
        }
        else
        {
            nBytes = ringSize_ - ( back_c_ - ring_c_ );
        }

        if ( nBytes > bufferSize )
        {
            nBytes = bufferSize;
        }

        memcpy( buffer, back_c_, nBytes );
        back_c_ += nBytes;

        if ( back_c_ >= ring_c_ + ringSize_ )
        {
            back_c_ = ring_c_;
        }

        if ( front_c_ == back_c_ )
        {
            front_c_ = back_c_ = ring_c_;
        }
    }

    isExhausted = ( front_c_ == back_c_ );

    this->unlock();

    return nBytes;
}

/**************************************************************************************************************/
unsigned
LoggerQueue::overflows() const
{
    return overflows_a_;
}

/**************************************************************************************************************/
size_t
LoggerQueue::write( uint8_t byte )
{
    this->lock();

    *front_c_++ = byte;

    if ( front_c_ >= ring_c_ + ringSize_ )
    {
        front_c_ = ring_c_;
    }

    if ( front_c_ == back_c_ )
    {
        ++overflows_a_;

        if ( ++back_c_ >= ring_c_ + ringSize_ )
        {
            back_c_ = ring_c_;
        }
    }

    this->unlock();

    return 1;
}

/**************************************************************************************************************/
Logger::Logger( SdFile* file, unsigned ringSize ) :
    LoggerQueue( ringSize ),
    file_( file )
{
}

/**************************************************************************************************************/
void
Logger::routine()
{
    for ( ;; )
    {
        unsigned long   cycleTime( millis() );
        static uint8_t  buffer[ WRITE_BUFFER_SIZE_ ];
        bool            isExhausted;
        unsigned        nBytes( pull(buffer, sizeof(buffer), isExhausted) );

        file_->write( buffer, nBytes );

        static unsigned long  lastFlushTime( 0 );

        if ( cycleTime >= lastFlushTime + FLUSH_INTERVAL_ )
        {
            file_->flush();
            lastFlushTime = cycleTime;
        }

        if ( isExhausted )
        {
            if ( isStopped() )
            {
                break;
            }
            else
            {
                unsigned  pastDuration( millis() - cycleTime );

                if ( pastDuration < SLEEP_INTERVAL_ )
                {
                    chThdSleepMilliseconds( SLEEP_INTERVAL_ - pastDuration ); 
                }
            }
        }
    }
}
