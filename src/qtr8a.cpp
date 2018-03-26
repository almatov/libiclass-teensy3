/* qtr8a.cpp
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

#include <cstdint>
#include <cstdio>
#include <Arduino.h>
#include "qtr8a.h"

using namespace std;
using namespace iclass;

const int       SENSORS_PITCH_      ( 9500 );   // micrometers
const int       POOR_RANGE_         ( 20 );     // percentage

const int       LEFT_EDGE_BOUND_    ( -(SENSORS_PITCH_ * 7) >> 1 );
const int       RIGHT_EDGE_BOUND_   ( (SENSORS_PITCH_ * 7) >> 1 );

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
    int         lineWidth,
    int         readBits,
    bool        inverse
) :
    lineWidth_( lineWidth ),
    readRange_( 1 << readBits ),
    inverse_( inverse )
{
    pins_[ 0 ] = pin1;
    pins_[ 1 ] = pin2;
    pins_[ 2 ] = pin3;
    pins_[ 3 ] = pin4;
    pins_[ 4 ] = pin5;
    pins_[ 5 ] = pin6;
    pins_[ 6 ] = pin7;
    pins_[ 7 ] = pin8;

    for ( int i = 0; i < 8; ++i )
    {
        pinMode( pins_[i], INPUT );
    }
}

/**************************************************************************************************************/
void
Qtr8a::read()
{
    int     minimum( readRange_ - 1 );
    int     maximum( 0 );

    for ( int i = 0; i < 8; ++i )
    {
        int     raw( analogRead(pins_[i]) );

        raws_[ i ] = raw;
        
        if ( minimum > raw )
        {
            minimum = raw;
        }

        if ( maximum < raw )
        {
            maximum = raw;
        }
    }

    int     range( maximum - minimum );

    threshold_ = minimum + ( range << 2 ) / 5;
    relativeRange_ = range * 100 / readRange_;
}

/**************************************************************************************************************/
int
Qtr8a::deviation() const
{
    if ( relativeRange_ <= POOR_RANGE_ )
    {
        return 0;
    }

    int     redge( rightEdge_() );
    int     ledge( leftEdge_() );

    if ( redge == RIGHT_EDGE_BOUND_ )
    {
        if ( redge - ledge < lineWidth_ )
        {
            return ledge + ( lineWidth_ >> 1 );
        }
        else if ( ledge > LEFT_EDGE_BOUND_ )
        {
            return redge - ( lineWidth_ >> 1 );
        }
    }

    if ( ledge == LEFT_EDGE_BOUND_ )
    {
        if ( redge - ledge < lineWidth_ )
        {
            return redge - ( lineWidth_ >> 1 );
        }
        else if ( redge < RIGHT_EDGE_BOUND_ )
        {
            return ledge + ( lineWidth_ >> 1 );
        }
    }
    
    return ( ledge + redge ) >> 1;
}

/**************************************************************************************************************/
bool
Qtr8a::isEmpty() const
{
    return ( relativeRange_ <= POOR_RANGE_ ) && ( threshold_ <= (readRange_ >> 1) );
}

/**************************************************************************************************************/
bool
Qtr8a::isFull() const
{
    return ( relativeRange_ <= POOR_RANGE_ ) && ( threshold_ > (readRange_ >> 1) );
}

/**************************************************************************************************************/
const char*
Qtr8a::dump() const
{
    snprintf
    (
        dumpBuffer_,
        sizeof( dumpBuffer_ ),
        "[%d] %d %d %d %d %d %d %d %d [%d%%]",
        threshold_,
        raws_[ 7 ],
        raws_[ 6 ],
        raws_[ 5 ],
        raws_[ 4 ],
        raws_[ 3 ],
        raws_[ 2 ],
        raws_[ 1 ],
        raws_[ 0 ],
        relativeRange_
    );

    return dumpBuffer_;
}

/**************************************************************************************************************/
int
Qtr8a::leftEdge_() const
{
    int     edge( LEFT_EDGE_BOUND_ );
    int     prev( raws_[7] );

    if ( (prev < threshold_) ^ inverse_ )
    {
        const int*  next( raws_ + 6 );

        while ( next >= raws_ )
        {
            if ( (*next >= threshold_) ^ inverse_ )
            {
                edge += ( threshold_ - prev ) * SENSORS_PITCH_ / ( *next - prev );

                break;
            }

            edge += SENSORS_PITCH_;
            prev = *next--;
        }
    }

    return edge;
}

/**************************************************************************************************************/
int
Qtr8a::rightEdge_() const
{
    int     edge( RIGHT_EDGE_BOUND_ );
    int     prev( raws_[0] );

    if ( (prev < threshold_) ^ inverse_ )
    {
        const int*  next( raws_ + 1 );

        while ( next <= raws_ + 7 )
        {
            if ( (*next >= threshold_) ^ inverse_ )
            {
                edge -= ( threshold_ - prev ) * SENSORS_PITCH_ / ( *next - prev );

                break;
            }

            edge -= SENSORS_PITCH_;
            prev = *next++;
        }
    }

    return edge;
}

