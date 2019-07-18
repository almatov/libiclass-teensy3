/* meanfilter.h
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

#ifndef LIBICLASS_MEANFILTER_H_
#define LIBICLASS_MEANFILTER_H_ 1

#include "filter.h"

namespace iclass
{
    /**********************************************************************************************************/
    class MeanFilter : public Filter
    {

    public:

                                        MeanFilter( unsigned size=6 );
        virtual                         ~MeanFilter();

        virtual void                    put( int value ) override;
        virtual int                     get() const override;

    protected:

        int*                            ring_;
        int*                            oldest_;
        long                            sum_;
    };
}

#endif  // LIBICLASS_MEANFILTER_H_
