/* vnh.cpp
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

#include <Arduino.h>

#include "vnh.h"

using namespace iclass;

const double    KCS_    ( 0.13 );

/**************************************************************************************************************/
Vnh::Vnh
(
    uint8_t     enPin,
    uint8_t     ainPin,
    uint8_t     binPin,
    uint8_t     pwmPin,
    uint8_t     csPin
) :
    enPin_( enPin ),
    ainPin_( ainPin ),
    binPin_( binPin ),
    pwmPin_( pwmPin ),
    csPin_( csPin ),
    pwm_( 0 )
{
    pinMode( enPin_, OUTPUT );
    pinMode( ainPin_, OUTPUT );
    pinMode( binPin_, OUTPUT );
    pinMode( pwmPin_, OUTPUT );
    pinMode( csPin_, INPUT );

    stop();
}

/**************************************************************************************************************/
void
Vnh::start()
{
    digitalWrite( enPin_, HIGH );
}

/**************************************************************************************************************/
void
Vnh::stop()
{
    pwm_ = 0;

    analogWrite( pwmPin_, pwm_ );
    digitalWrite( ainPin_, HIGH );
    digitalWrite( binPin_, HIGH );
    digitalWrite( enPin_, LOW );
}

/**************************************************************************************************************/
void
Vnh::setPwm( int pwm )
{
    if ( pwm == 0 )
    {
        analogWrite( pwmPin_, 0 );
        digitalWrite( ainPin_, HIGH );
        digitalWrite( binPin_, HIGH );
    }
    else if ( pwm > 0 && pwm_ < 0 )
    {
        digitalWrite( ainPin_, HIGH );
        analogWrite( pwmPin_, pwm );
        digitalWrite( binPin_, LOW );
    }
    else if ( pwm > 0 && pwm_ == 0 )
    {
        analogWrite( pwmPin_, pwm );
        digitalWrite( binPin_, LOW );
    }
    else if ( pwm < 0 && pwm_ > 0 )
    {
        digitalWrite( binPin_, HIGH );
        analogWrite( pwmPin_, -pwm );
        digitalWrite( ainPin_, LOW );
    }
    else if ( pwm < 0 && pwm_ == 0 )
    {
        analogWrite( pwmPin_, -pwm );
        digitalWrite( ainPin_, LOW );
    }
    else
    {
        analogWrite( pwmPin_, (pwm > 0)? pwm : -pwm );
    }

    pwm_ = pwm;
}

/**************************************************************************************************************/
float
Vnh::current( int arBits, float aref )
{
    double  kAmper( static_cast<double>(aref) / ((1<<arBits) - 1) / KCS_ );
    
    return analogRead( csPin_ ) * kAmper;
}
