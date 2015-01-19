//
//  win_lock.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__win_lock__
#define __threadpp__win_lock__

#include <windows.h>

namespace threadpp
{
    class win_lock
    {
        CRITICAL_SECTION _mutex;
        CONDITION_VARIABLE _cond;
        volatile unsigned int _owner;
        volatile unsigned int _count;
        void operator=(const win_lock& l){};
        win_lock(const win_lock& l){};
    public:
        win_lock();
        ~win_lock();
        void lock();
        void unlock();
        void wait();
        void wait(unsigned long millisecs);
        void notify();
        void notify_all();
    };
}

#include "win_lock.hpp"
#endif /* defined(__threadpp__win_lock__) */
