//
//  std_lock.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__std_lock__
#define __threadpp__std_lock__
#include <mutex>
#include <condition_variable>
namespace threadpp
{
    class std_lock
    {
        std::mutex _mutex;
        std::condition_variable_any _cond;
        void operator=(const std_lock& l){};
        std_lock(const std_lock& l){};
    public:
        std_lock();
        ~std_lock();
        void lock();
        void unlock();
        void wait();
        void wait(unsigned long millisecs);
        void notify();
        void notify_all();
    };
}

#endif /* defined(__threadpp__std_lock__) */
