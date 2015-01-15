//
//  std_recursivelock.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__std_recursivelock__
#define __threadpp__std_recursivelock__
#include <mutex>
#include <condition_variable>
namespace threadpp
{
    class std_recursivelock
    {
        std::recursive_mutex _mutex;
        std::unique_lock<std::recursive_mutex> _lock;
        std::condition_variable_any _cond;
        void operator=(const std_recursivelock& l){};
        std_recursivelock(const std_recursivelock& l){};
    public:
        std_recursivelock();
        ~std_recursivelock();
        void lock();
        void unlock();
        void wait();
        void wait(unsigned long millisecs);
        void notify();
        void notify_all();
    };
}

#endif /* defined(__threadpp__std_recursivelock__) */
