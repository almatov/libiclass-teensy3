/* quadratureencoder.h
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

#ifndef LIBICLASS_QUADRATUREENCODER_H_
#define LIBICLASS_QUADRATUREENCODER_H_ 1

#include <atomic>
#include <cstdint>

#include "encoder.h"

namespace iclass
{
    /**********************************************************************************************************/
    class QuadratureEncoder : public Encoder
    {

    public:

                                        QuadratureEncoder
                                        (
                                            unsigned  cpr,
                                            uint8_t   pin1,
                                            uint8_t   pin2,
                                            unsigned  zeroInterval = 1000   // microseconds
                                        );

        virtual void                    update() override;

    protected:

        void                            interruptUpdate_();

        const unsigned                  zeroInterval_;

        volatile uint8_t*               pin1Register_;
        volatile uint8_t*               pin2Register_;
        uint8_t                         pin1Bitmask_;
        uint8_t                         pin2Bitmask_;
        int                             state_;
        std::atomic<long>               cumulativeDelta_a_;
    };
}

#endif  // LIBICLASS_QUADRATUREENCODER_H_
