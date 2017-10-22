/* task.cpp
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

#include "task.h"

using namespace iclass;

/**************************************************************************************************************/
Task::Task() :
    thread_( nullptr ),
    isStarted_a_( false ),
    isStopped_a_( false ),
    isFinished_a_( false )
{
}

/**************************************************************************************************************/
Task::~Task()
{
}

/**************************************************************************************************************/
void
Task::start( tprio_t prio )
{
    if ( !isStarted_a_ )
    {
        isStarted_a_ = true;
        thread_ = chThdCreateStatic( wa_(), waSize_(), prio, Task::routine_, this );
    }
}

/**************************************************************************************************************/
void
Task::stop()
{
    if ( !isStopped_a_ && isStarted_a_ )
    {
        isStopped_a_ = true;

        if ( thread_ && !isFinished_a_ )
        {
            chThdWait( thread_ );
        }
    }
}

/**************************************************************************************************************/
void            
Task::routine_( void* vTask )
{
    Task*  task( reinterpret_cast<Task*>(vTask) );

    task->routine();
    task->isFinished_a_ = true;
    chThdExit( MSG_OK );
}
