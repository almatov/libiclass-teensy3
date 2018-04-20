/* tb6612.h
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

#ifndef LIBICLASS_TB6612_H_
#define LIBICLASS_TB6612_H_ 1

#include <cstdint>

namespace iclass
{
    /**********************************************************************************************************/
    class Tb6612
    {

    public:

                                        Tb6612
                                        (
                                            uint8_t  stbyPin,
                                            uint8_t  ain1Pin,
                                            uint8_t  ain2Pin,
                                            uint8_t  apwmPin,
                                            uint8_t  bin1Pin,
                                            uint8_t  bin2Pin,
                                            uint8_t  bpwmPin
                                        );

        void                            start();
        void                            stop();
        void                            setPwmA( int pwm );
        void                            setPwmB( int pwm );

    protected:

        const uint8_t                   stbyPin_;
        const uint8_t                   ain1Pin_;
        const uint8_t                   ain2Pin_;
        const uint8_t                   apwmPin_;
        const uint8_t                   bin1Pin_;
        const uint8_t                   bin2Pin_;
        const uint8_t                   bpwmPin_;

        int                             pwmA_;
        int                             pwmB_;
    };
}

#endif  // LIBICLASS_TB6612_H_
