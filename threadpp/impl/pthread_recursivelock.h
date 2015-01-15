//
//  pthread_recursivelock.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__pthread_recursivelock__
#define __threadpp__pthread_recursivelock__
//extern "C"
//{
#include <pthread.h>
//}
namespace threadpp
{
    class pthread_recursivelock
    {
        pthread_mutex_t _mutex;
        pthread_cond_t _cond;
        void operator=(const pthread_recursivelock& l){};
        pthread_recursivelock(const pthread_recursivelock& l){};
    public:
        pthread_recursivelock();
        ~pthread_recursivelock();
        void lock();
        void unlock();
        void wait();
        void wait(unsigned long millisecs);
        void notify();
        void notify_all();
    };
}
#endif /* defined(__threadpp__pthread_recursivelock__) */
