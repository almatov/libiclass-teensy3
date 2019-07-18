/* task.h
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

#ifndef LIBICLASS_TASK_H_
#define LIBICLASS_TASK_H_ 1

#include <atomic>
#include <ch.h>

namespace iclass
{
    /**********************************************************************************************************/
    class Task // abstract
    {

    public:

                                        Task();
                                        Task( const Task& ) = delete;
        virtual                         ~Task();

        Task&                           operator =( const Task& ) = delete;

        void                            start( tprio_t =NORMALPRIO+1 );
        void                            stop();

        bool                            isStarted() const;
        bool                            isStopped() const;
        bool                            isFinished() const;

        virtual void                    routine() = 0;

    private:

        virtual stkalign_t*             wa_() = 0;
        virtual size_t                  waSize_() const =0;

        static void                     routine_( void* );

        thread_t*                       thread_;
        std::atomic<bool>               isStarted_a_;
        std::atomic<bool>               isStopped_a_;
        std::atomic<bool>               isFinished_a_;
    };

    /**********************************************************************************************************/
    template <unsigned N>
    class ChTask : public Task
    {

    public:

        virtual                         ~ChTask();

    private:

        virtual stkalign_t*             wa_();
        virtual size_t                  waSize_() const;

                                        THD_WORKING_AREA( twa_, N );
    };
}

/*
****************************************************************************************************************
****************************************************************************************************************
*/

namespace iclass
{
    //---------------------------------------------------------------------------------------------------------
    inline bool
    Task::isStarted() const
    {
        return isStarted_a_;
    }

    //---------------------------------------------------------------------------------------------------------
    inline bool
    Task::isStopped() const
    {
        return isStopped_a_;
    }

    //---------------------------------------------------------------------------------------------------------
    inline bool
    Task::isFinished() const
    {
        return isFinished_a_;
    }

    //---------------------------------------------------------------------------------------------------------
    template <unsigned N>
    ChTask<N>::~ChTask()
    {
    }

    //---------------------------------------------------------------------------------------------------------
    template <unsigned N>
    stkalign_t*
    ChTask<N>::wa_()
    {
        return twa_;
    }

    //---------------------------------------------------------------------------------------------------------
    template <unsigned N>
    size_t
    ChTask<N>::waSize_() const
    {
        return sizeof( twa_ );
    }
}

#endif // LIBICLASS_TASK_H_
