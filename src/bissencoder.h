/* bissencoder.h
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

#ifndef LIBICLASS_BISSENCODER_H_
#define LIBICLASS_BISSENCODER_H_ 1

#include <atomic>
#include <cstdint>

#include "encoder.h"
#include "task.h"

namespace iclass
{
    /**********************************************************************************************************/
    class BissEncoder : public Encoder, public ChTask<64>
    {

    public:

                                        BissEncoder
                                        (
                                            unsigned    bits,       // [1-30]
                                            uint8_t     clockPin,
                                            uint8_t     dataPin
                                        );

                                        ~BissEncoder();

        virtual void                    update() override;
        virtual void                    routine() override;

        int                             position() const;           // thread safe
        unsigned                        transmitErrors() const;     // thread safe
        unsigned                        deviceErrors() const;       // thread safe
        unsigned                        deviceWarnings() const;     // thread safe

    protected:

        void                            routineUpdate_();

        const unsigned                  bits_;
        const uint8_t                   clockPin_;
        const uint8_t                   dataPin_;

        std::atomic<int>                position_;
        std::atomic<long>               cumulativeDelta_;
        std::atomic<unsigned>           transmitErrors_;
        std::atomic<unsigned>           deviceErrors_;
        std::atomic<unsigned>           deviceWarnings_;
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
    BissEncoder::position() const
    {
        return position_;
    }

    //---------------------------------------------------------------------------------------------------------
    inline unsigned
    BissEncoder::transmitErrors() const
    {
        return transmitErrors_;
    }

    //---------------------------------------------------------------------------------------------------------
    inline unsigned
    BissEncoder::deviceErrors() const
    {
        return deviceErrors_;
    }

    //---------------------------------------------------------------------------------------------------------
    inline unsigned
    BissEncoder::deviceWarnings() const
    {
        return deviceWarnings_;
    }
}

#endif  // LIBICLASS_BISSENCODER_H_
