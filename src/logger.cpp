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

static const unsigned  SLEEP_INTERVAL_      ( 30 );     // milliseconds
static const unsigned  FLUSH_INTERVAL_      ( 300 );    // milliseconds
static const unsigned  WRITE_BLOCK_SIZE_    ( 1024 );   // bytes

/**************************************************************************************************************/
LoggerQueue::LoggerQueue( unsigned ringSize ) :
    ringSize_( ringSize ),
    queueSize_a_( 0 ),
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
LoggerQueue::queueSize() const
{
    return queueSize_a_;
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
        ++queueSize_a_;
    }

    this->unlock();

    return 1;
}

/**************************************************************************************************************/
void
LoggerQueue::initialShift_( uint8_t* swapBuffer, int shiftBytes )
{
    this->lock();

    if ( queueSize_a_ > 0 )
    {
        if ( back_c_ > ring_ )
        {
            shiftBytes -= back_c_ - ring_;

            if ( shiftBytes > 0 )
            {
                memcpy( swapBuffer, ring_ + ringSize_ - shiftBytes, shiftBytes );
                memmove( ring_ + shiftBytes, ring_, ringSize_ - shiftBytes );
                memcpy( ring_, swapBuffer, shiftBytes );
            }
            else if ( shiftBytes < 0 )
            {
                memcpy( swapBuffer, ring_, -shiftBytes );
                memmove( ring_, ring_ - shiftBytes, ringSize_ + shiftBytes );
                memcpy( ring_ + ringSize_ + shiftBytes, swapBuffer, -shiftBytes );
            }
        }
        else
        {
            int     swapBytes( (front_c_ + shiftBytes) - (ring_ + ringSize_) );

            if ( swapBytes <= 0 )
            {
                memmove( back_c_ + shiftBytes, back_c_, queueSize_a_ - swapBytes );
            }
            else
            {
                memcpy( swapBuffer, front_c_ - swapBytes, swapBytes );
                memmove( back_c_ + shiftBytes, back_c_, queueSize_a_ - swapBytes );
                memcpy( ring_, swapBuffer, swapBytes );
            }
        }
    }

    front_c_ += shiftBytes;
    back_c_ += shiftBytes;

    if ( front_c_ >= ring_ + ringSize_ )
    {
        front_c_ -= ringSize_;
    }

    if ( back_c_ >= ring_ + ringSize_ )
    {
        back_c_ -= ringSize_;
    }

    this->unlock();
}

/**************************************************************************************************************/
unsigned
LoggerQueue::pull_( uint8_t* block, unsigned blockSize )
{
    unsigned  pullBytes( 0 );

    this->lock();

    if ( front_c_ != back_c_ )
    {
        if ( front_c_ > back_c_ )
        {
            pullBytes = front_c_ - back_c_;
        }
        else
        {
            pullBytes = ringSize_ - ( back_c_ - ring_ );
        }

        if ( pullBytes > blockSize )
        {
            pullBytes = blockSize;
        }

        memcpy( block, back_c_, pullBytes );
        back_c_ += pullBytes;
        queueSize_a_ -= pullBytes;

        if ( back_c_ >= ring_ + ringSize_ )
        {
            back_c_ = ring_;
        }
    }

    this->unlock();

    return pullBytes;
}

/**************************************************************************************************************/
Logger::Logger( const char* fileName, unsigned ringSize ) :
    LoggerQueue( ringSize ),
    fileName_( fileName ),
    fileSize_a_( 0 ),
    writes_a_( 0 ),
    writeBytes_a_( 0 )
{
}

/**************************************************************************************************************/
unsigned long
Logger::fileSize() const
{
    return fileSize_a_;
}

/**************************************************************************************************************/
unsigned
Logger::writes() const
{
    return writes_a_;
}

/**************************************************************************************************************/
unsigned
Logger::writeBytes() const
{
    return writeBytes_a_;
}

/**************************************************************************************************************/
void
Logger::routine()
{
    SdFile  logFile;

    if ( !logFile.open(fileName_, O_WRONLY | O_APPEND | O_CREAT) )
    {
        return;
    }

    uint8_t*    block( new uint8_t[WRITE_BLOCK_SIZE_] );

    fileSize_a_ = logFile.fileSize();
    initialShift_( block, fileSize_a_ % WRITE_BLOCK_SIZE_ );

    unsigned long   nextFlushTime( millis() + FLUSH_INTERVAL_ );

    while ( true )
    {
        unsigned long   cycleStartTime( millis() );
        unsigned        nBytes( pull_(block, WRITE_BLOCK_SIZE_ - (fileSize_a_%WRITE_BLOCK_SIZE_)) );

        if ( nBytes > 0 )
        {
            ++writes_a_;
            writeBytes_a_ = nBytes;
            logFile.write( block, nBytes );
            fileSize_a_ += nBytes;
        }

        if ( queueSize_a_ >= WRITE_BLOCK_SIZE_ )
        {
            continue;
        }

        if ( cycleStartTime >= nextFlushTime )
        {
            logFile.flush();
            nextFlushTime += FLUSH_INTERVAL_;
        }

        if ( queueSize_a_ == 0 && isStopped() )
        {
            break;
        }

        unsigned    cycleDuration( millis() - cycleStartTime );

        if ( cycleDuration < SLEEP_INTERVAL_ )
        {
            chThdSleepMilliseconds( SLEEP_INTERVAL_ - cycleDuration ); 
        }
    }

    delete[] block;
    logFile.close();
}
