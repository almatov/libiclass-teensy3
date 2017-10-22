/* filter.h
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

#ifndef LIBICLASS_FILTER_H_
#define LIBICLASS_FILTER_H_ 1

namespace iclass
{
    /**********************************************************************************************************/
    class Filter // abstract
    {

    public:

                                        Filter( unsigned size );
        virtual                         ~Filter();

        virtual void                    put( int value ) = 0;
        virtual int                     get() const = 0;

        int                             operator ()( int value );

    protected:

        unsigned                        size_;
        unsigned                        nElements_;
    };
}

#endif  // LIBICLASS_FILTER_H_
