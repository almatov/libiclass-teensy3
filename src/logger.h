/* logger.h
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

#ifndef LIBICLASS_LOGGER_H_
#define LIBICLASS_LOGGER_H_ 1

#include <Print.h>

#include "common.h"
#include "task.h"

namespace iclass
{
    /**********************************************************************************************************/
    class LoggerQueue : public Common, public Print
    {

    public:

                                        LoggerQueue( unsigned ringSize );
                                        ~LoggerQueue();

        unsigned                        queueSize() const;
        unsigned                        overflows() const;

        virtual size_t                  write( uint8_t );

    protected:

        void                            initialShift_( uint8_t* swapBuffer, int shiftBytes );
        unsigned                        pull_( uint8_t* block, unsigned blockSize );

        const unsigned                  ringSize_;
        uint8_t*                        ring_;

        uint8_t*                        front_c_;
        uint8_t*                        back_c_;

        std::atomic<unsigned>           queueSize_a_;
        std::atomic<unsigned>           overflows_a_;
    };

    /**********************************************************************************************************/
    class Logger : public ChTask<1024>, public LoggerQueue
    {

    public:

                                        Logger( const char* fileName, unsigned ringSize=8192 );

        unsigned long                   fileSize() const;
        unsigned                        writes() const;
        unsigned                        writeBytes() const;

        virtual void                    routine();

    protected:

        const char*                     fileName_;

        std::atomic<unsigned long>      fileSize_a_;
        std::atomic<unsigned>           writes_a_;
        std::atomic<unsigned>           writeBytes_a_;
    };
}

#endif  // LIBICLASS_LOGGER_H_
