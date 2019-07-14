/* encoder.cpp
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

#include "encoder.h"

using namespace iclass;

/**************************************************************************************************************/
Encoder::Encoder( unsigned long cpr ) :
    cpr_( cpr ),
    kRpm_( 60000000.0f / cpr_ ),
    delta_( 0 ),
    interval_( 0 ),
    time_( 0 ),
    counts_( 0.0f )
{
}

/**************************************************************************************************************/
long
Encoder::delta() const
{
    return delta_;
}

/**************************************************************************************************************/
float
Encoder::rotations() const
{
    return counts_ / cpr_;
}

/**************************************************************************************************************/
float
Encoder::rpm() const
{
    return delta_? (kRpm_ * delta_ / interval_) : 0.0f;
}
