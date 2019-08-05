/* vnh.h
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

#ifndef LIBICLASS_VNH_H_
#define LIBICLASS_VNH_H_ 1

#include <cstdint>

namespace iclass
{
    /**********************************************************************************************************/
    class Vnh
    {

    public:

                                        Vnh
                                        (
                                            uint8_t     enPin,
                                            uint8_t     ainPin,
                                            uint8_t     binPin,
                                            uint8_t     pwmPin,
                                            uint8_t     csPin
                                        );

        void                            start();
        void                            stop();
        void                            setPwm( int pwm );
        float                           current( int arBits=10, float aref=3.3 );

    protected:

        const uint8_t                   enPin_;
        const uint8_t                   ainPin_;
        const uint8_t                   binPin_;
        const uint8_t                   pwmPin_;
        const uint8_t                   csPin_;
        int                             pwm_;
    };
}

#endif  // LIBICLASS_VNH_H_
