/* medianfilter.cpp
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

#include "medianfilter.h"

using namespace iclass;

/**************************************************************************************************************/
MedianFilter::MedianFilter( unsigned size ) :
    Filter( size )
{
    ring_ = new Element[ size_ ];
    oldest_ = ring_;
    oldest_->upper = oldest_;
    oldest_->lower = oldest_;
    min_ = premedian_ = oldest_;
}

/**************************************************************************************************************/
MedianFilter::~MedianFilter()
{
    delete[] ring_;
}

/**************************************************************************************************************/
void
MedianFilter::put( int value )
{
    if ( nElements_ )
    {
        if ( nElements_ == size_ )
        {
            detach_( oldest_ );
        }

        attach_( value );
    }

    oldest_->value = value;

    if ( nElements_ < size_ )
    {
        ++nElements_;
    }

    if ( ++oldest_ >= ring_ + size_ )
    {
        oldest_ = ring_;
    }
}

/**************************************************************************************************************/
int
MedianFilter::get() const
{
    if ( nElements_ & 0x1 )      // odd
    {
        return premedian_->value;
    }
    else if ( nElements_ > 0 )   // even
    {
        return ( premedian_->value + premedian_->upper->value ) >> 1;
    }

    return 0;
}

/**************************************************************************************************************/
void
MedianFilter::clear()
{
    nElements_ = 0;
    oldest_ = ring_;
    oldest_->upper = oldest_;
    oldest_->lower = oldest_;
    min_ = premedian_ = oldest_;
}

/**************************************************************************************************************/
void
MedianFilter::attach_( int value )
{
    if ( value <= premedian_->value )
    {
        if ( value <= min_->value )
        {
            oldest_->upper = min_;
            oldest_->lower = min_->lower;
            min_->lower->upper = oldest_;
            min_->lower = oldest_;
            min_ = oldest_;
        }
        else
        {
            Element*  e( premedian_->lower );

            while ( value < e->value )
            {
                e = e->lower;
            }

            oldest_->upper = e->upper;
            oldest_->lower = e;
            e->upper->lower = oldest_;
            e->upper = oldest_;
        }

        if ( nElements_ & 0x1 )
        {
            premedian_ = premedian_->lower;
        }
    }
    else
    {
        if ( value >= min_->lower->value )
        {
            oldest_->upper = min_;
            oldest_->lower = min_->lower;
            min_->lower->upper = oldest_;
            min_->lower = oldest_;
        }
        else
        {
            Element*  e( premedian_ );

            while ( value > e->value )
            {
                e = e->upper;
            }

            oldest_->upper = e;
            oldest_->lower = e->lower;
            e->lower->upper = oldest_;
            e->lower = oldest_;
        }

        if ( !(nElements_ & 0x1) )
        {
            premedian_ = premedian_->upper;
        }
    }
}

/**************************************************************************************************************/
void
MedianFilter::detach_( Element* element )
{
    element->upper->lower = element->lower;
    element->lower->upper = element->upper;
    --nElements_;

    if ( element == min_ )
    {
        min_ = element->upper;
    }

    int  position;

    if ( element == premedian_ )
    {
        position = 0;
    }
    else if ( element->value < premedian_->value )
    {
        position = -1;
    }
    else if ( element->value > premedian_->value )
    {
        position = 1;
    }
    else
    {
        for ( Element* e(element);; e = e->lower )
        {
            if ( e == min_ || e->value < element->value )
            {
                position = -1;

                break;
            }
            else if ( e == premedian_ )
            {
                position = 1;

                break;
            }
        }
    }

    if ( !(nElements_ & 0x1) && position >= 0 )
    {
        premedian_ = premedian_->lower;
    }
    else if ( (nElements_ & 0x1) && position <= 0 )
    {
        premedian_ = premedian_->upper;
    }
}
