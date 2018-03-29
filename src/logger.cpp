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

#include <SdFat.h>
#include "logger.h"

using namespace iclass;

const unsigned  SLEEP_INTERVAL_     ( 30 );         // milliseconds
const unsigned  FLUSH_INTERVAL_     ( 300 );        // milliseconds
const unsigned  WRITE_BLOCK_SIZE_   ( 1024 );       // bytes

/**************************************************************************************************************/
LoggerQueue::LoggerQueue( unsigned ringSize ) :
    ringSize_( ringSize ),
    size_a_( 0 ),
    overflows_a_( 0 )
{
    ring_ = new uint8_t[ ringSize_ ];
    front_c_ = ring_;
    back_c_ = ring_;
}

/**************************************************************************************************************/
LoggerQueue::~LoggerQueue()
{
    this->lock();

    delete[] ring_;
}

/**************************************************************************************************************/
unsigned
LoggerQueue::size() const
{
    return size_a_;
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

    if ( front_c_ >= ring_ + ringSize_ )
    {
        front_c_ = ring_;
    }

    if ( front_c_ == back_c_ )
    {
        ++overflows_a_;

        if ( ++back_c_ >= ring_ + ringSize_ )
        {
            back_c_ = ring_;
        }
    }
    else
    {
        ++size_a_;
    }

    this->unlock();

    return 1;
}

/**************************************************************************************************************/
unsigned
LoggerQueue::pull_( uint8_t* block, unsigned blockSize )
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
            nBytes = ringSize_ - ( back_c_ - ring_ );
        }

        if ( nBytes > blockSize )
        {
            nBytes = blockSize;
        }

        memcpy( block, back_c_, nBytes );
        back_c_ += nBytes;
        size_a_ -= nBytes;

        if ( back_c_ >= ring_ + ringSize_ )
        {
            back_c_ = ring_;
        }
    }

    this->unlock();

    return nBytes;
}

/**************************************************************************************************************/
Logger::Logger( const char* fileName, unsigned ringSize ) :
    LoggerQueue( ringSize ),
    fileName_( fileName )
{
}

/**************************************************************************************************************/
void
Logger::routine()
{
    SdFile  logFile;

    logFile.open( fileName_, O_WRONLY | O_APPEND | O_CREAT );

    uint8_t*        block( new uint8_t[WRITE_BLOCK_SIZE_] );
    unsigned long   nextFlushTime( millis() + FLUSH_INTERVAL_ );

    while ( true )
    {
        unsigned long   cycleStartTime( millis() );
        unsigned        nBytes( pull_(block, WRITE_BLOCK_SIZE_) );

        if ( nBytes > 0 )
        {
            logFile.write( block, nBytes );
        }

        if ( size_a_ >= WRITE_BLOCK_SIZE_ )
        {
            continue;
        }

        if ( cycleStartTime >= nextFlushTime )
        {
            logFile.flush();
            nextFlushTime += FLUSH_INTERVAL_;
        }

        if ( isStopped() )
        {
            break;
        }
        else
        {
            unsigned    pastDuration( millis() - cycleStartTime );

            if ( pastDuration < SLEEP_INTERVAL_ )
            {
                chThdSleepMilliseconds( SLEEP_INTERVAL_ - pastDuration ); 
            }
        }
    }

    delete[] block;
    logFile.close();
}
