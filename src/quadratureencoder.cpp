/* quadratureencoder.cpp
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

#include "quadratureencoder.h"

using namespace std;
using namespace iclass;

struct QuadratureEncoder_ : QuadratureEncoder
{
    using QuadratureEncoder::interruptUpdate_;
};

static QuadratureEncoder_*   interruptArgs_[ 58 ];

/**************************************************************************************************************/
static void
isr0_()
{
    interruptArgs_[ 0 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr1_()
{
    interruptArgs_[ 1 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr2_()
{
    interruptArgs_[ 2 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr3_()
{
    interruptArgs_[ 3 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr4_()
{
    interruptArgs_[ 4 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr5_()
{
    interruptArgs_[ 5 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr6_()
{
    interruptArgs_[ 6 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr7_()
{
    interruptArgs_[ 7 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr8_()
{
    interruptArgs_[ 8 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr9_()
{
    interruptArgs_[ 9 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr10_()
{
    interruptArgs_[ 10 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr11_()
{
    interruptArgs_[ 11 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr12_()
{
    interruptArgs_[ 12 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr13_()
{
    interruptArgs_[ 13 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr14_()
{
    interruptArgs_[ 14 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr15_()
{
    interruptArgs_[ 15 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr16_()
{
    interruptArgs_[ 16 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr17_()
{
    interruptArgs_[ 17 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr18_()
{
    interruptArgs_[ 18 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr19_()
{
    interruptArgs_[ 19 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr20_()
{
    interruptArgs_[ 20 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr21_()
{
    interruptArgs_[ 21 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr22_()
{
    interruptArgs_[ 22 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr23_()
{
    interruptArgs_[ 23 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr24_()
{
    interruptArgs_[ 24 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr25_()
{
    interruptArgs_[ 25 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr26_()
{
    interruptArgs_[ 26 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr27_()
{
    interruptArgs_[ 27 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr28_()
{
    interruptArgs_[ 28 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr29_()
{
    interruptArgs_[ 29 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr30_()
{
    interruptArgs_[ 30 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr31_()
{
    interruptArgs_[ 31 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr32_()
{
    interruptArgs_[ 32 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr33_()
{
    interruptArgs_[ 33 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr34_()
{
    interruptArgs_[ 34 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr35_()
{
    interruptArgs_[ 35 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr36_()
{
    interruptArgs_[ 36 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr37_()
{
    interruptArgs_[ 37 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr38_()
{
    interruptArgs_[ 38 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr39_()
{
    interruptArgs_[ 39 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr40_()
{
    interruptArgs_[ 40 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr41_()
{
    interruptArgs_[ 41 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr42_()
{
    interruptArgs_[ 42 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr43_()
{
    interruptArgs_[ 43 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr44_()
{
    interruptArgs_[ 44 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr45_()
{
    interruptArgs_[ 45 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr46_()
{
    interruptArgs_[ 46 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr47_()
{
    interruptArgs_[ 47 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr48_()
{
    interruptArgs_[ 48 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr49_()
{
    interruptArgs_[ 49 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr50_()
{
    interruptArgs_[ 50 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr51_()
{
    interruptArgs_[ 51 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr52_()
{
    interruptArgs_[ 52 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr53_()
{
    interruptArgs_[ 53 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr54_()
{
    interruptArgs_[ 54 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr55_()
{
    interruptArgs_[ 55 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr56_()
{
    interruptArgs_[ 56 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
isr57_()
{
    interruptArgs_[ 57 ]->interruptUpdate_();
}

/**************************************************************************************************************/
static void
attachQuadratureEncoderInterrupt_( uint8_t pin, QuadratureEncoder_* encoder )
{
    switch ( pin )
    {
        case 0:

            interruptArgs_[ 0 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(0), isr0_, CHANGE );
            break;

        case 1:

            interruptArgs_[ 1 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(1), isr1_, CHANGE );
            break;

        case 2:

            interruptArgs_[ 2 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(2), isr2_, CHANGE );
            break;

        case 3:

            interruptArgs_[ 3 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(3), isr3_, CHANGE );
            break;

        case 4:

            interruptArgs_[ 4 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(4), isr4_, CHANGE );
            break;

        case 5:

            interruptArgs_[ 5 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(5), isr5_, CHANGE );
            break;

        case 6:

            interruptArgs_[ 6 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(6), isr6_, CHANGE );
            break;

        case 7:

            interruptArgs_[ 7 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(7), isr7_, CHANGE );
            break;

        case 8:

            interruptArgs_[ 8 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(8), isr8_, CHANGE );
            break;

        case 9:

            interruptArgs_[ 9 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(9), isr9_, CHANGE );
            break;

        case 10:

            interruptArgs_[ 10 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(10), isr10_, CHANGE );
            break;

        case 11:

            interruptArgs_[ 11 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(11), isr11_, CHANGE );
            break;

        case 12:

            interruptArgs_[ 12 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(12), isr12_, CHANGE );
            break;

        case 13:

            interruptArgs_[ 13 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(13), isr13_, CHANGE );
            break;

        case 14:

            interruptArgs_[ 14 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(14), isr14_, CHANGE );
            break;

        case 15:

            interruptArgs_[ 15 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(15), isr15_, CHANGE );
            break;

        case 16:

            interruptArgs_[ 16 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(16), isr16_, CHANGE );
            break;

        case 17:

            interruptArgs_[ 17 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(17), isr17_, CHANGE );
            break;

        case 18:

            interruptArgs_[ 18 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(18), isr18_, CHANGE );
            break;

        case 19:

            interruptArgs_[ 19 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(19), isr19_, CHANGE );
            break;

        case 20:

            interruptArgs_[ 20 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(20), isr20_, CHANGE );
            break;

        case 21:

            interruptArgs_[ 21 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(21), isr21_, CHANGE );
            break;

        case 22:

            interruptArgs_[ 22 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(22), isr22_, CHANGE );
            break;

        case 23:

            interruptArgs_[ 23 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(23), isr23_, CHANGE );
            break;

        case 24:

            interruptArgs_[ 24 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(24), isr24_, CHANGE );
            break;

        case 25:

            interruptArgs_[ 25 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(25), isr25_, CHANGE );
            break;

        case 26:

            interruptArgs_[ 26 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(26), isr26_, CHANGE );
            break;

        case 27:

            interruptArgs_[ 27 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(27), isr27_, CHANGE );
            break;

        case 28:

            interruptArgs_[ 28 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(28), isr28_, CHANGE );
            break;

        case 29:

            interruptArgs_[ 29 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(29), isr29_, CHANGE );
            break;

        case 30:

            interruptArgs_[ 30 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(30), isr30_, CHANGE );
            break;

        case 31:

            interruptArgs_[ 31 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(31), isr31_, CHANGE );
            break;

        case 32:

            interruptArgs_[ 32 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(32), isr32_, CHANGE );
            break;

        case 33:

            interruptArgs_[ 33 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(33), isr33_, CHANGE );
            break;

        case 34:

            interruptArgs_[ 34 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(34), isr34_, CHANGE );
            break;

        case 35:

            interruptArgs_[ 35 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(35), isr35_, CHANGE );
            break;

        case 36:

            interruptArgs_[ 36 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(36), isr36_, CHANGE );
            break;

        case 37:

            interruptArgs_[ 37 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(37), isr37_, CHANGE );
            break;

        case 38:

            interruptArgs_[ 38 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(38), isr38_, CHANGE );
            break;

        case 39:

            interruptArgs_[ 39 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(39), isr39_, CHANGE );
            break;

        case 40:

            interruptArgs_[ 40 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(40), isr40_, CHANGE );
            break;

        case 41:

            interruptArgs_[ 41 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(41), isr41_, CHANGE );
            break;

        case 42:

            interruptArgs_[ 42 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(42), isr42_, CHANGE );
            break;

        case 43:

            interruptArgs_[ 43 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(43), isr43_, CHANGE );
            break;

        case 44:

            interruptArgs_[ 44 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(44), isr44_, CHANGE );
            break;

        case 45:

            interruptArgs_[ 45 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(45), isr45_, CHANGE );
            break;

        case 46:

            interruptArgs_[ 46 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(46), isr46_, CHANGE );
            break;

        case 47:

            interruptArgs_[ 47 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(47), isr47_, CHANGE );
            break;

        case 48:

            interruptArgs_[ 48 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(48), isr48_, CHANGE );
            break;

        case 49:

            interruptArgs_[ 49 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(49), isr49_, CHANGE );
            break;

        case 50:

            interruptArgs_[ 50 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(50), isr50_, CHANGE );
            break;

        case 51:

            interruptArgs_[ 51 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(51), isr51_, CHANGE );
            break;

        case 52:

            interruptArgs_[ 52 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(52), isr52_, CHANGE );
            break;

        case 53:

            interruptArgs_[ 53 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(53), isr53_, CHANGE );
            break;

        case 54:

            interruptArgs_[ 54 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(54), isr54_, CHANGE );
            break;

        case 55:

            interruptArgs_[ 55 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(55), isr55_, CHANGE );
            break;

        case 56:

            interruptArgs_[ 56 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(56), isr56_, CHANGE );
            break;

        case 57:

            interruptArgs_[ 57 ] = encoder;
            attachInterrupt( digitalPinToInterrupt(57), isr57_, CHANGE );
            break;
    }
}

/**************************************************************************************************************/
QuadratureEncoder::QuadratureEncoder
(
    unsigned  cpr,
    uint8_t   pin1,
    uint8_t   pin2,
    unsigned  zeroInterval
) :
    Encoder( cpr ),
    zeroInterval_( zeroInterval ),
    state_( 0 ),
    cumulativeDelta_( 0 )
{
    pinMode( pin1, INPUT_PULLUP );
    pinMode( pin2, INPUT_PULLUP );
    pin1Register_ = portInputRegister( digitalPinToPort(pin1) );
    pin1Bitmask_ = digitalPinToBitMask( pin1 );
    pin2Register_ = portInputRegister( digitalPinToPort(pin2) );
    pin2Bitmask_ = digitalPinToBitMask( pin2 );
    delayMicroseconds( 2000 );

    if ( *pin1Register_ & pin1Bitmask_ )
    {
        state_ |= 1;
    }

    if ( *pin2Register_ & pin2Bitmask_ )
    {
        state_ |= 2;
    }

    attachQuadratureEncoderInterrupt_( pin1, reinterpret_cast<QuadratureEncoder_*>(this) );
    attachQuadratureEncoderInterrupt_( pin2, reinterpret_cast<QuadratureEncoder_*>(this) );
}

/**************************************************************************************************************/
void
QuadratureEncoder::update()
{
    unsigned long  now( micros() );

    if ( cumulativeDelta_ == 0 && now >= time_ + zeroInterval_ )
    {
        interval_ = ( now - time_ ) % zeroInterval_;
        time_ = now - interval_;
        delta_ = 0;
    }
    else
    {
        interval_ = now - time_;
        time_ = now;
        delta_ = cumulativeDelta_.exchange( 0 );
        counts_ += delta_;
    }
}

/**************************************************************************************************************/
/*
                                  _______         _______
                      Pin1 ______|       |_______|       |______ Pin1
        negative <---         _______         _______         __      --> positive
                      Pin2 __|       |_______|       |_______|   Pin2

        new     new     old     old
        pin2    pin1    pin2    pin1    Result
        ----    ----    ----    ----    ------
        0       0       0       0       0       no movement
        0       0       0       1       +1
        0       0       1       0       -1
        0       0       1       1       +2      assume pin1 edges only
        0       1       0       0       -1
        0       1       0       1       0       no movement
        0       1       1       0       -2      assume pin1 edges only
        0       1       1       1       +1
        1       0       0       0       +1
        1       0       0       1       -2      assume pin1 edges only
        1       0       1       0       0       no movement
        1       0       1       1       -1
        1       1       0       0       +2      assume pin1 edges only
        1       1       0       1       -1
        1       1       1       0       +1
        1       1       1       1       0       no movement
*/
void
QuadratureEncoder::interruptUpdate_()
{
    int  newState( state_ >> 2 );

    if ( *pin1Register_ & pin1Bitmask_)
    {
        newState |= 4;
    }

    if ( *pin2Register_ & pin2Bitmask_ )
    {
        newState |= 8;
    }

    switch ( newState )
    {
        case 1:
        case 7:
        case 8:
        case 14:

            cumulativeDelta_ += 1;
            break;

        case 2:
        case 4:
        case 11:
        case 13:

            cumulativeDelta_ -= 1;
            break;

        case 3:
        case 12:

            cumulativeDelta_ += 2;
            break;

        case 6:
        case 9:

            cumulativeDelta_ -= 2;
    }

    state_ = newState;
}
