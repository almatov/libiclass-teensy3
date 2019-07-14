/* common.h
****************************************************************************************************************
****************************************************************************************************************

    Copyright (C) 2004-2006, 2008-2011, 2013, 2015, 2017 Askar Almatov

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

#ifndef LIBICLASS_COMMON_H_
#define LIBICLASS_COMMON_H_ 1

#include <ch.h>

namespace iclass
{
    /**********************************************************************************************************/
    class Common
    {

    public:

                                        Common();
                                        Common( const Common& ) = delete;

        Common&                         operator =( const Common& ) = delete;

	    void                            lock();
	    void                            unlock();

    private:

                                        MUTEX_DECL( mutex_ );
    };
}

#endif // LIBICLASS_COMMON_H_
