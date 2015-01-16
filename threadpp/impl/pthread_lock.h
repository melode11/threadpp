//
//  pthread_lock.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__pthread_lock__
#define __threadpp__pthread_lock__
//extern "C"
//{
#include <pthread.h>
//}
namespace threadpp
{
    class pthread_lock
    {
        pthread_mutex_t _mutex;
        pthread_cond_t _cond;
        void operator=(const pthread_lock& l){};
        pthread_lock(const pthread_lock& l){};
    public:
        pthread_lock();
        ~pthread_lock();
        void lock();
        void unlock();
        void wait();
        void wait(unsigned long millisecs);
        void notify();
        void notify_all();
    };
}
#endif /* defined(__threadpp__pthread_lock__) */
