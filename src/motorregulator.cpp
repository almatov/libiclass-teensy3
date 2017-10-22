/* motorregulator.cpp
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

#include "motorregulator.h"

using namespace iclass;

/**************************************************************************************************************/
MotorRegulator::MotorRegulator
(
    int     pwmBits,
    float   vBattery,
    float   vMotor,
    float   kV,
    float   kP
) :
    maxPwm_( static_cast<float>((1<<pwmBits) - 1) / vBattery * vMotor ),
    kPwm_( static_cast<float>((1<<pwmBits) - 1) / vBattery / kV ),
    kP_( kP )
{
}

/**************************************************************************************************************/
int
MotorRegulator::computePwm( int rpm, int targetRpm )
{
    int     targetPwm( kPwm_ * targetRpm );
    int     error( targetRpm - rpm );
    int     pwm( targetPwm + kP_ * error );

    if ( pwm > maxPwm_ )
    {
        pwm = maxPwm_;
    }
    else if ( pwm < -maxPwm_ )
    {
        pwm = - maxPwm_;
    }

    return pwm;
}
