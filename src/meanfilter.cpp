/* meanfilter.cpp
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

#include "meanfilter.h"

using namespace iclass;

/**************************************************************************************************************/
MeanFilter::MeanFilter( unsigned size ) :
    Filter( size ),
    sum_( 0 )
{
    ring_ = new int[ size_ ];
    oldest_ = ring_;
}

/**************************************************************************************************************/
MeanFilter::~MeanFilter()
{
    delete[] ring_;
}

/**************************************************************************************************************/
void
MeanFilter::put( int value )
{
    if ( nElements_ < size_ )
    {
        ++nElements_;
    }
    else
    {
        sum_ -= *oldest_;
    }

    sum_ += value;
    *oldest_ = value;

    if ( ++oldest_ >= ring_ + size_ )
    {
        oldest_ = ring_;
    }
}

/**************************************************************************************************************/
int
MeanFilter::get() const
{
    return sum_? sum_/static_cast<long>(nElements_) : 0;
}
