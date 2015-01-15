//
//  win_recursivelock.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__win_recursivelock__
#define __threadpp__win_recursivelock__

#include <windows.h>

namespace threadpp
{
    class win_recursivelock
    {
        CRITICAL_SECTION _mutex;
        CONDITION_VARIABLE _cond;
        volatile unsigned int _owner;
        volatile unsigned int _count;
        void operator=(const win_recursivelock& l){};
        win_recursivelock(const win_recursivelock& l){};
    public:
        win_recursivelock();
        ~win_recursivelock();
        void lock();
        void unlock();
        void wait();
        void wait(unsigned long millisecs);
        void notify();
        void notify_all();
    };
}


#endif /* defined(__threadpp__win_recursivelock__) */
