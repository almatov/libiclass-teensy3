/* absoluteencoder.h
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

#ifndef LIBICLASS_ABSOLUTEENCODER_H_
#define LIBICLASS_ABSOLUTEENCODER_H_ 1

#include <Arduino.h>
#include "encoder.h"

namespace iclass
{
    /**********************************************************************************************************/
    class AbsoluteEncoder : public Encoder
    {

    public:

                                        AbsoluteEncoder( int bits, uint8_t clockPin, uint8_t dataPin );

        virtual void                    update() override;

    protected:

        const int                       bits_;
        const uint8_t                   clockPin_;
        const uint8_t                   dataPin_;
        int                             state_;
    };
}

#endif  // LIBICLASS_ABSOLUTEENCODER_H_
