/* absoluteencoder.h
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

#ifndef LIBICLASS_ABSOLUTEENCODER_H_
#define LIBICLASS_ABSOLUTEENCODER_H_ 1

#include <atomic>
#include <cstdint>

#include "encoder.h"
#include "task.h"

namespace iclass
{
    /**********************************************************************************************************/
    class AbsoluteEncoder : public Encoder, public ChTask<64>
    {

    public:

                                        AbsoluteEncoder
                                        (
                                            unsigned    bits,       // [1-31]
                                            uint8_t     clockPin,
                                            uint8_t     dataPin
                                        );

                                        ~AbsoluteEncoder();

        virtual void                    update() override;
        virtual void                    routine() override;

        int                             position() const;           // thread safe

    protected:

        void                            routineUpdate_();

        const unsigned                  bits_;
        const uint8_t                   clockPin_;
        const uint8_t                   dataPin_;

        std::atomic<int>                position_;
        std::atomic<long>               cumulativeDelta_;
    };
}

/*
****************************************************************************************************************
****************************************************************************************************************
*/

namespace iclass
{
    //---------------------------------------------------------------------------------------------------------
    inline int
    AbsoluteEncoder::position() const
    {
        return position_;
    }
}

#endif  // LIBICLASS_ABSOLUTEENCODER_H_
