/* qtr8a.h
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

#ifndef LIBICLASS_QTR8A_H_
#define LIBICLASS_QTR8A_H_ 1

#include <cstdint>

namespace iclass
{
    /**********************************************************************************************************/
    class Qtr8a
    {    

    public:
                                        Qtr8a
                                        (
                                            uint8_t     pin1,
                                            uint8_t     pin2,
                                            uint8_t     pin3,
                                            uint8_t     pin4,
                                            uint8_t     pin5,
                                            uint8_t     pin6,
                                            uint8_t     pin7,
                                            uint8_t     pin8,
                                            int         lineWidth,          // millimeters
                                            int         readBits = 10,
                                            bool        inverse = false
                                        );

        void                            read();
        double                          deviation() const;                  // millimeters
        bool                            isEmpty() const;
        bool                            isFull() const;
        const char*                     dump() const;

    protected:

        int                             leftEdge_() const;
        int                             rightEdge_() const;
        int                             uDeviation_() const;

        uint8_t                         pins_[ 8 ];
        const int                       lineWidth_;
        const int                       readRange_;
        const bool                      inverse_;
        int                             raws_[ 8 ];
        int                             threshold_;
        int                             relativeRange_;
        mutable char                    dumpBuffer_[ 54];
    };
}

#endif  // LIBICLASS_QTR8A_H_
