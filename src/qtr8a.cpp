/* qtr8a.cpp
****************************************************************************************************************
****************************************************************************************************************

    Copyright (C) 2017 Askar Almatov

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

#include <cstdint>
#include <Arduino.h>
#include "qtr8a.h"

using namespace iclass;

const int       STEP( 2375 );           // micrometers
const int       DIVIDER( 1000 );        // micrometers to millimeters
const uint32_t  FULL( (0x1<<29) - 1 );

/**************************************************************************************************************/
Qtr8a::Qtr8a
(
    uint8_t     pin1,
    uint8_t     pin2,
    uint8_t     pin3,
    uint8_t     pin4,
    uint8_t     pin5,
    uint8_t     pin6,
    uint8_t     pin7,
    uint8_t     pin8,
    int         mmLineWidth,
    int         threshold,
    bool        inverse
) :
    stepsLineWidth_( (mmLineWidth*DIVIDER) / STEP ),
    threshold_( threshold ),
    inverse_( inverse ),
    bits_( FULL )
{
    pins_[ 0 ] = pin1;
    pins_[ 1 ] = pin2;
    pins_[ 2 ] = pin3;
    pins_[ 3 ] = pin4;
    pins_[ 4 ] = pin5;
    pins_[ 5 ] = pin6;
    pins_[ 6 ] = pin7;
    pins_[ 7 ] = pin8;

    pinMode( pins_[0], INPUT );
    pinMode( pins_[1], INPUT );
    pinMode( pins_[2], INPUT );
    pinMode( pins_[3], INPUT );
    pinMode( pins_[4], INPUT );
    pinMode( pins_[5], INPUT );
    pinMode( pins_[6], INPUT );
    pinMode( pins_[7], INPUT );
}

/**************************************************************************************************************/
void
Qtr8a::read()
{
    raw_[ 0 ] = analogRead( pins_[0] );
    raw_[ 4 ] = analogRead( pins_[1] );
    raw_[ 8 ] = analogRead( pins_[2] );
    raw_[ 12 ] = analogRead( pins_[3] );
    raw_[ 16 ] = analogRead( pins_[4] );
    raw_[ 20 ] = analogRead( pins_[5] );
    raw_[ 24 ] = analogRead( pins_[6] );
    raw_[ 28 ] = analogRead( pins_[7] );

    raw_[ 2 ] = ( raw_[0] + raw_[4] ) >> 1;
    raw_[ 6 ] = ( raw_[4] + raw_[8] ) >> 1;
    raw_[ 10 ] = ( raw_[8] + raw_[12] ) >> 1;
    raw_[ 14 ] = ( raw_[12] + raw_[16] ) >> 1;
    raw_[ 18 ] = ( raw_[16] + raw_[20] ) >> 1;
    raw_[ 22 ] = ( raw_[20] + raw_[24] ) >> 1;
    raw_[ 26 ] = ( raw_[24] + raw_[28] ) >> 1;

    raw_[ 1 ] = ( raw_[0] + raw_[2] ) >> 1;
    raw_[ 3 ] = ( raw_[2] + raw_[4] ) >> 1;
    raw_[ 5 ] = ( raw_[4] + raw_[6] ) >> 1;
    raw_[ 7 ] = ( raw_[6] + raw_[8] ) >> 1;
    raw_[ 9 ] = ( raw_[8] + raw_[10] ) >> 1;
    raw_[ 11 ] = ( raw_[10] + raw_[12] ) >> 1;
    raw_[ 13 ] = ( raw_[12] + raw_[14] ) >> 1;
    raw_[ 15 ] = ( raw_[14] + raw_[16] ) >> 1;
    raw_[ 17 ] = ( raw_[16] + raw_[18] ) >> 1;
    raw_[ 19 ] = ( raw_[18] + raw_[20] ) >> 1;
    raw_[ 21 ] = ( raw_[20] + raw_[22] ) >> 1;
    raw_[ 23 ] = ( raw_[22] + raw_[24] ) >> 1;
    raw_[ 25 ] = ( raw_[24] + raw_[26] ) >> 1;
    raw_[ 27 ] = ( raw_[26] + raw_[28] ) >> 1;

    bits_ = 0;
    bits_ |= ( raw_[0] > threshold_ ) ^ inverse_;
    bits_ |= ( (raw_[1] > threshold_) ^ inverse_ ) << 1;
    bits_ |= ( (raw_[2] > threshold_) ^ inverse_ ) << 2;
    bits_ |= ( (raw_[3] > threshold_) ^ inverse_ ) << 3;
    bits_ |= ( (raw_[4] > threshold_) ^ inverse_ ) << 4;
    bits_ |= ( (raw_[5] > threshold_) ^ inverse_ ) << 5;
    bits_ |= ( (raw_[6] > threshold_) ^ inverse_ ) << 6;
    bits_ |= ( (raw_[7] > threshold_) ^ inverse_ ) << 7;
    bits_ |= ( (raw_[8] > threshold_) ^ inverse_ ) << 8;
    bits_ |= ( (raw_[9] > threshold_) ^ inverse_ ) << 9;
    bits_ |= ( (raw_[10] > threshold_) ^ inverse_ ) << 10;
    bits_ |= ( (raw_[11] > threshold_) ^ inverse_ ) << 11;
    bits_ |= ( (raw_[12] > threshold_) ^ inverse_ ) << 12;
    bits_ |= ( (raw_[13] > threshold_) ^ inverse_ ) << 13;
    bits_ |= ( (raw_[14] > threshold_) ^ inverse_ ) << 14;
    bits_ |= ( (raw_[15] > threshold_) ^ inverse_ ) << 15;
    bits_ |= ( (raw_[16] > threshold_) ^ inverse_ ) << 16;
    bits_ |= ( (raw_[17] > threshold_) ^ inverse_ ) << 17;
    bits_ |= ( (raw_[18] > threshold_) ^ inverse_ ) << 18;
    bits_ |= ( (raw_[19] > threshold_) ^ inverse_ ) << 19;
    bits_ |= ( (raw_[20] > threshold_) ^ inverse_ ) << 20;
    bits_ |= ( (raw_[21] > threshold_) ^ inverse_ ) << 21;
    bits_ |= ( (raw_[22] > threshold_) ^ inverse_ ) << 22;
    bits_ |= ( (raw_[23] > threshold_) ^ inverse_ ) << 23;
    bits_ |= ( (raw_[24] > threshold_) ^ inverse_ ) << 24;
    bits_ |= ( (raw_[25] > threshold_) ^ inverse_ ) << 25;
    bits_ |= ( (raw_[26] > threshold_) ^ inverse_ ) << 26;
    bits_ |= ( (raw_[27] > threshold_) ^ inverse_ ) << 27;
    bits_ |= ( (raw_[28] > threshold_) ^ inverse_ ) << 28;
}

/**************************************************************************************************************/
uint32_t
Qtr8a::bits() const
{
    return bits_;
}

/**************************************************************************************************************/
int
Qtr8a::leftEdge() const
{
    int     edge( -14 );

    for ( uint32_t mask = 0x1<<28; mask && !(bits_&mask); mask >>= 1 )
    {
        ++edge;
    }

    return edge;
}

/**************************************************************************************************************/
int
Qtr8a::rightEdge() const
{
    int     edge( 14 );
    
    for ( uint32_t mask = 0x1; mask && !(bits_&mask); mask <<= 1 )
    {
        --edge;
    }

    return edge;
}

/**************************************************************************************************************/
int
Qtr8a::deviation() const
{
    if ( bits_ == 0 )
    {
        return 0;
    }

    int     redge( rightEdge() );
    int     ledge( leftEdge() );

    if ( redge == 14 )
    {
        if ( redge - ledge < stepsLineWidth_ )
        {
            return ledge + ( stepsLineWidth_ >> 1 );
        }
        else if ( ledge > -14 )
        {
            return redge - ( stepsLineWidth_ >> 1 );
        }
    }

    if ( ledge == -14 )
    {
        if ( redge - ledge < stepsLineWidth_ )
        {
            return redge - ( stepsLineWidth_ >> 1 );
        }
        else if ( redge < 14 )
        {
            return ledge + ( stepsLineWidth_ >> 1 );
        }
    }
    
    return ( ledge + redge ) >> 1;
}

/**************************************************************************************************************/
bool
Qtr8a::isEmpty() const
{
    return bits_ == 0;
}

/**************************************************************************************************************/
bool
Qtr8a::isFull() const
{
    return bits_ == FULL;
}
