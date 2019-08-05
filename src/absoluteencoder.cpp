/* absoluteencoder.cpp
****************************************************************************************************************
****************************************************************************************************************

    Copyright (C) 2017, 2019 Askar Almatov

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

#include <Arduino.h>

#include "absoluteencoder.h"

using namespace iclass;

/**************************************************************************************************************/
AbsoluteEncoder::AbsoluteEncoder( unsigned bits, uint8_t clockPin, uint8_t dataPin ) :
    Encoder( 1 << bits ),
    bits_( bits ),
    clockPin_( clockPin ),
    dataPin_( dataPin ),
    position_a_( 0 ),
    cumulativeDelta_a_( 0 )
{
    pinMode( clockPin_, OUTPUT );
    pinMode( dataPin_, INPUT_PULLUP );
    digitalWrite( clockPin_, HIGH );
}

/**************************************************************************************************************/
AbsoluteEncoder::~AbsoluteEncoder()
{
}

/**************************************************************************************************************/
void
AbsoluteEncoder::update()
{
    unsigned long   now( micros() );

    interval_ = now - time_;
    time_ = now;
    delta_ = cumulativeDelta_a_.exchange( 0 );
    counts_ += delta_;
}

/**************************************************************************************************************/
void
AbsoluteEncoder::routine()
{
    chThdSleepMicroseconds( 500 );      // waiting for ready
    routineUpdate_();                   // set current position
    cumulativeDelta_a_ = 0;               // ignore first delta
    chThdSleepMicroseconds( 100 );      // bus reset interval

    while ( !isStopped() )
    {
        routineUpdate_();
        chThdSleepMilliseconds( 1 );
    }
}

/**************************************************************************************************************/
void
AbsoluteEncoder::routineUpdate_()
{
    unsigned    gray( 0 );

    for ( int i = bits_ - 1; i >= 0; --i )
    {
        digitalWrite( clockPin_, LOW );
        digitalWrite( clockPin_, HIGH );
        gray |= digitalRead( dataPin_ ) << i;
    }

    int     newPosition( 0 );

    for ( ; gray; gray >>= 1 )
    {
        newPosition ^= gray;
    }

    long    momentaryDelta( (newPosition - position_a_.exchange(newPosition)) & (cpr_ - 1) );

    if ( momentaryDelta & (cpr_ >> 1) )
    {
        momentaryDelta -= cpr_;
    }

    cumulativeDelta_a_ += momentaryDelta;
}
