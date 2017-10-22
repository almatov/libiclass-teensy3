/* medianfilter.h
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

#ifndef LIBICLASS_MEDIANFILTER_H_
#define LIBICLASS_MEDIANFILTER_H_ 1

#include "filter.h"

namespace iclass
{
    /**********************************************************************************************************/
    class MedianFilter : public Filter
    {

    public:

        struct Element;

                                        MedianFilter( unsigned size=6 );
        virtual                         ~MedianFilter();

        virtual void                    put( int value ) override;
        virtual int                     get() const override;

        void                            clear();

    protected:

        void                            attach_( int );
        void                            detach_( Element* );

        Element*                        ring_;
        Element*                        oldest_;
        Element*                        min_;
        Element*                        premedian_;
    };

    /**********************************************************************************************************/
    struct MedianFilter::Element
    {
        int                             value;
        Element*                        upper;
        Element*                        lower;
    };
}

#endif  // LIBICLASS_MEDIANFILTER_H_
