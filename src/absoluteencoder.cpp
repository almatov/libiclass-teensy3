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
    dataPin_( dataPin )
{
    pinMode( clockPin_, OUTPUT );
    pinMode( dataPin_, INPUT_PULLUP );
    delayMicroseconds( 100 );

    digitalWrite( clockPin_, HIGH );
    delayMicroseconds( 1000 );

    position_ = 0;
    update();
    counts_ = 0.0f;
}

/**************************************************************************************************************/
void
AbsoluteEncoder::update()
{
    unsigned long   now( micros() );
    unsigned        gray( 0 );

    for ( int i = bits_; i > 0; --i )
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

    int     newDelta( (newPosition - position_) & (cpr_ - 1) );

    if ( newDelta & (cpr_ >> 1) )
    {
        newDelta -= cpr_;
    }

    delta_ = newDelta;
    interval_ = now - time_;
    time_ = now;
    counts_ += delta_;
    position_ = newPosition;
}
