/* motorregulator.h
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

#ifndef LIBICLASS_MOTORREGULATOR_H_
#define LIBICLASS_MOTORREGULATOR_H_ 1

namespace iclass
{
    /**********************************************************************************************************/
    class MotorRegulator
    {

    public:

                                        MotorRegulator
                                        (
                                            int    pwmBits,
                                            float  vBattery,
                                            float  vMotor,
                                            float  kV,
                                            float  kP
                                        );

        int                             computePwm( int rpm, int targetRpm );

    protected:

        const int                       maxPwm_;
        const float                     kPwm_;
        const float                     kP_;
    };
}

#endif  // LIBICLASS_MOTORREGULATOR_H_
