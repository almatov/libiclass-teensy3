/* tb6612.cpp
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

#include <Arduino.h>

#include "tb6612.h"

using namespace iclass;

/**************************************************************************************************************/
Tb6612::Tb6612
(
    uint8_t  stbyPin,
    uint8_t  ain1Pin,
    uint8_t  ain2Pin,
    uint8_t  apwmPin,
    uint8_t  bin1Pin,
    uint8_t  bin2Pin,
    uint8_t  bpwmPin
) :
    stbyPin_( stbyPin ),
    ain1Pin_( ain1Pin ),
    ain2Pin_( ain2Pin ),
    apwmPin_( apwmPin ),
    bin1Pin_( bin1Pin ),
    bin2Pin_( bin2Pin ),
    bpwmPin_( bpwmPin )
{
    pinMode( stbyPin_, OUTPUT );
    pinMode( ain1Pin_, OUTPUT );
    pinMode( ain2Pin_, OUTPUT );
    pinMode( apwmPin_, OUTPUT );
    pinMode( bin1Pin_, OUTPUT );
    pinMode( bin2Pin_, OUTPUT );
    pinMode( bpwmPin_, OUTPUT );

    stop();
}

/**************************************************************************************************************/
void
Tb6612::start()
{
    digitalWrite( stbyPin_, HIGH );
}

/**************************************************************************************************************/
void
Tb6612::stop()
{
    pwmA_ = 0;
    pwmB_ = 0;

    digitalWrite( stbyPin_, LOW );
    digitalWrite( ain1Pin_, HIGH );
    digitalWrite( ain2Pin_, HIGH );
    analogWrite( apwmPin_, pwmA_ );
    digitalWrite( bin1Pin_, HIGH );
    digitalWrite( bin2Pin_, HIGH );
    analogWrite( bpwmPin_, pwmB_ );
}

/**************************************************************************************************************/
void
Tb6612::setPwmA( int pwm )
{
    if ( pwm == 0 )
    {
        analogWrite( apwmPin_, 0 );
        digitalWrite( ain1Pin_, HIGH );
        digitalWrite( ain2Pin_, HIGH );
    }
    else if ( pwm > 0 && pwmA_ < 0 )
    {
        digitalWrite( ain1Pin_, HIGH );
        analogWrite( apwmPin_, pwm );
        digitalWrite( ain2Pin_, LOW );
    }
    else if ( pwm > 0 && pwmA_ == 0 )
    {
        analogWrite( apwmPin_, pwm );
        digitalWrite( ain2Pin_, LOW );
    }
    else if ( pwm < 0 && pwmA_ > 0 )
    {
        digitalWrite( ain2Pin_, HIGH );
        analogWrite( apwmPin_, -pwm );
        digitalWrite( ain1Pin_, LOW );
    }
    else if ( pwm < 0 && pwmA_ == 0 )
    {
        analogWrite( apwmPin_, -pwm );
        digitalWrite( ain1Pin_, LOW );
    }
    else
    {
        analogWrite( apwmPin_, (pwm > 0)? pwm : -pwm );
    }

    pwmA_ = pwm;
}

/**************************************************************************************************************/
void
Tb6612::setPwmB( int pwm )
{
    if ( pwm == 0 )
    {
        analogWrite( bpwmPin_, 0 );
        digitalWrite( bin1Pin_, HIGH );
        digitalWrite( bin2Pin_, HIGH );
    }
    else if ( pwm > 0 && pwmB_ < 0 )
    {
        digitalWrite( bin1Pin_, HIGH );
        analogWrite( bpwmPin_, pwm );
        digitalWrite( bin2Pin_, LOW );
    }
    else if ( pwm > 0 && pwmB_ == 0 )
    {
        analogWrite( bpwmPin_, pwm );
        digitalWrite( bin2Pin_, LOW );
    }
    else if ( pwm < 0 && pwmB_ > 0 )
    {
        digitalWrite( bin2Pin_, HIGH );
        analogWrite( bpwmPin_, -pwm );
        digitalWrite( bin1Pin_, LOW );
    }
    else if ( pwm < 0 && pwmB_ == 0 )
    {
        analogWrite( bpwmPin_, -pwm );
        digitalWrite( bin1Pin_, LOW );
    }
    else
    {
        analogWrite( bpwmPin_, (pwm > 0)? pwm : -pwm );
    }

    pwmB_ = pwm;
}
