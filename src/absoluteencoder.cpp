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
AbsoluteEncoder::AbsoluteEncoder( int bits, uint8_t clockPin, uint8_t dataPin ) :
    Encoder( 0x1 << bits ),
    bits_( bits ),
    clockPin_( clockPin ),
    dataPin_( dataPin ),
    state_( 0 )
{
    pinMode( clockPin_, OUTPUT );
    pinMode( dataPin_, INPUT_PULLUP );
    delayMicroseconds( 100 );

    digitalWrite( clockPin_, HIGH );
    delayMicroseconds( 1000 );

    update();
    counts_ = 0.0f;
}

/**************************************************************************************************************/
void
AbsoluteEncoder::update()
{
    unsigned long  now( micros() );
    uint16_t       gray( 0 );

    for ( int i = bits_-1; i >= 0; --i )
    {
        digitalWrite( clockPin_, LOW );
        digitalWrite( clockPin_, HIGH );
        gray |= digitalRead( dataPin_ ) << i;
    }

    int  newState( 0 );

    for ( ; gray; gray >>= 1 )
    {
        newState ^= gray;
    }

    delta_ = ( newState - state_ ) & ( cpr_ - 1 );

    if ( delta_ >= (cpr_ >> 1) )
    {
        delta_ -= cpr_;
    }

    interval_ = now - time_;
    time_ = now;
    counts_ += delta_;
    state_ = newState;
}
