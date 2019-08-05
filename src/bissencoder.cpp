/* bissencoder.cpp
****************************************************************************************************************
****************************************************************************************************************

    Copyright (C) 2019 Askar Almatov

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

#include "bissencoder.h"

using namespace iclass;

static const uint8_t    CRC6_TABLE_[] =
{
    // width=6, poly=0x43, XOR 0x0 in, XOR 0x0 out, MSB first in, MSB first out
    0x00, 0x03, 0x06, 0x05, 0x0c, 0x0f, 0x0a, 0x09, 0x18, 0x1b, 0x1e, 0x1d, 0x14, 0x17, 0x12, 0x11,
    0x30, 0x33, 0x36, 0x35, 0x3c, 0x3f, 0x3a, 0x39, 0x28, 0x2b, 0x2e, 0x2d, 0x24, 0x27, 0x22, 0x21,
    0x23, 0x20, 0x25, 0x26, 0x2f, 0x2c, 0x29, 0x2a, 0x3b, 0x38, 0x3d, 0x3e, 0x37, 0x34, 0x31, 0x32,
    0x13, 0x10, 0x15, 0x16, 0x1f, 0x1c, 0x19, 0x1a, 0x0b, 0x08, 0x0d, 0x0e, 0x07, 0x04, 0x01, 0x02,
    0x05, 0x06, 0x03, 0x00, 0x09, 0x0a, 0x0f, 0x0c, 0x1d, 0x1e, 0x1b, 0x18, 0x11, 0x12, 0x17, 0x14,
    0x35, 0x36, 0x33, 0x30, 0x39, 0x3a, 0x3f, 0x3c, 0x2d, 0x2e, 0x2b, 0x28, 0x21, 0x22, 0x27, 0x24,
    0x26, 0x25, 0x20, 0x23, 0x2a, 0x29, 0x2c, 0x2f, 0x3e, 0x3d, 0x38, 0x3b, 0x32, 0x31, 0x34, 0x37,
    0x16, 0x15, 0x10, 0x13, 0x1a, 0x19, 0x1c, 0x1f, 0x0e, 0x0d, 0x08, 0x0b, 0x02, 0x01, 0x04, 0x07,
    0x0a, 0x09, 0x0c, 0x0f, 0x06, 0x05, 0x00, 0x03, 0x12, 0x11, 0x14, 0x17, 0x1e, 0x1d, 0x18, 0x1b,
    0x3a, 0x39, 0x3c, 0x3f, 0x36, 0x35, 0x30, 0x33, 0x22, 0x21, 0x24, 0x27, 0x2e, 0x2d, 0x28, 0x2b,
    0x29, 0x2a, 0x2f, 0x2c, 0x25, 0x26, 0x23, 0x20, 0x31, 0x32, 0x37, 0x34, 0x3d, 0x3e, 0x3b, 0x38,
    0x19, 0x1a, 0x1f, 0x1c, 0x15, 0x16, 0x13, 0x10, 0x01, 0x02, 0x07, 0x04, 0x0d, 0x0e, 0x0b, 0x08,
    0x0f, 0x0c, 0x09, 0x0a, 0x03, 0x00, 0x05, 0x06, 0x17, 0x14, 0x11, 0x12, 0x1b, 0x18, 0x1d, 0x1e,
    0x3f, 0x3c, 0x39, 0x3a, 0x33, 0x30, 0x35, 0x36, 0x27, 0x24, 0x21, 0x22, 0x2b, 0x28, 0x2d, 0x2e,
    0x2c, 0x2f, 0x2a, 0x29, 0x20, 0x23, 0x26, 0x25, 0x34, 0x37, 0x32, 0x31, 0x38, 0x3b, 0x3e, 0x3d,
    0x1c, 0x1f, 0x1a, 0x19, 0x10, 0x13, 0x16, 0x15, 0x04, 0x07, 0x02, 0x01, 0x08, 0x0b, 0x0e, 0x0d
};

/**************************************************************************************************************/
static unsigned
crc6_( unsigned data, int bits )
{
    unsigned    crc( 0 );

    for ( int shift = ((bits+1) >> 3) << 3; shift > 0; shift -= 8 )
    {
        crc = CRC6_TABLE_[ static_cast<uint8_t>((data>>shift) ^ (crc<<2)) ];
    }

    return CRC6_TABLE_[ static_cast<uint8_t>(data ^ (crc<<2)) ] ^ 0x3f;
}

/**************************************************************************************************************/
BissEncoder::BissEncoder( unsigned bits, uint8_t clockPin, uint8_t dataPin ) :
    Encoder( 0x1 << bits ),
    bits_( bits ),
    clockPin_( clockPin ),
    dataPin_( dataPin ),
    position_( 0 ),
    cumulativeDelta_( 0 ),
    transmitErrors_( 0 ),
    deviceErrors_( 0 ),
    deviceWarnings_( 0 )
{
    pinMode( clockPin_, OUTPUT );
    pinMode( dataPin_, INPUT_PULLUP );
    digitalWrite( clockPin_, HIGH );
}

/**************************************************************************************************************/
BissEncoder::~BissEncoder()
{
}

/**************************************************************************************************************/
void
BissEncoder::update()
{
    unsigned long   now( micros() );

    interval_ = now - time_;
    time_ = now;
    delta_ = cumulativeDelta_.exchange( 0 );
    counts_ += delta_;
}

/**************************************************************************************************************/
void
BissEncoder::routine()
{
    chThdSleepMicroseconds( 500 );      // waiting for ready
    routineUpdate_( true );             // set current position, ignore power-on device error
    cumulativeDelta_ = 0;               // ignore first delta
    chThdSleepMicroseconds( 100 );      // bus reset interval

    while ( !isStopped() )
    {
        routineUpdate_();
        chThdSleepMilliseconds( 1 );
    }
}

/**************************************************************************************************************/
void
BissEncoder::routineUpdate_( bool ignoreDeviceError )
{
    unsigned    preamble( 0 );
    unsigned    data( 0 );
    unsigned    crc( 0 );

    for ( int i = 4; i > 0; --i )
    {
        digitalWrite( clockPin_, LOW );
        digitalWrite( clockPin_, HIGH );
        preamble <<= 1;
        preamble |= digitalRead( dataPin_ );
    }

    for ( int i = bits_ + 2; i > 0; --i )
    {
        digitalWrite( clockPin_, LOW );
        digitalWrite( clockPin_, HIGH );
        data <<= 1;
        data |= digitalRead( dataPin_ );
    }

    for ( int i = 6; i > 0; --i )
    {
        digitalWrite( clockPin_, LOW );
        digitalWrite( clockPin_, HIGH );
        crc <<= 1;
        crc |= digitalRead( dataPin_ );
    }

    if ( preamble != 0xa || crc != crc6_(data, bits_) )
    {
        ++transmitErrors_;

        return;
    }

    if ( !ignoreDeviceError && !(data & 0x2) )
    {
        ++deviceErrors_;

        return;
    }

    if ( !(data & 0x1) )
    {
        ++deviceWarnings_;
    }

    int     newPosition( data >> 2 );
    long    momentaryDelta( (newPosition - position_.exchange(newPosition)) & (cpr_ - 1) );

    if ( momentaryDelta & (cpr_ >> 1) )
    {
        momentaryDelta -= cpr_;
    }

    cumulativeDelta_ += momentaryDelta;
}
