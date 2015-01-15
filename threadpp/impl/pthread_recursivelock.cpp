//
//  pthread_recursivelock.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include "pthread_recursivelock.h"
#include "../threadpp_assert.h"
#include <errno.h>
#include <cstring>
namespace threadpp{
    pthread_recursivelock::pthread_recursivelock()
    {
        pthread_mutexattr_t mattr;
        pthread_mutexattr_init(&mattr);
        pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&_mutex, &mattr);
        pthread_mutexattr_destroy(&mattr);
        pthread_condattr_t cattr;
        pthread_condattr_init(&cattr);
        pthread_cond_init(&_cond, &cattr);
        pthread_condattr_destroy(&cattr);
    }
    
    pthread_recursivelock::~pthread_recursivelock()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }
    
    void pthread_recursivelock::lock()
    {
        int code = pthread_mutex_lock(&_mutex);
        ASSERT(code == 0, "lock failed,error:%s",strerror(code));
    }
    
    void pthread_recursivelock::unlock()
    {
        int code = pthread_mutex_unlock(&_mutex);
        ASSERT(code == 0, "unlock failed,error:%s",strerror(code));
    }
    
    void pthread_recursivelock::wait()
    {
        int code = pthread_cond_wait(&_cond, &_mutex);
        ASSERT(code == 0 || code == ETIMEDOUT, "wait failed,error:%s",strerror(code));
    }
    
    void pthread_recursivelock::wait(unsigned long millisecs)
    {
        struct timespec ts = (struct timespec){.tv_sec = long(millisecs/1000),.tv_nsec = long((millisecs%1000)*1000000)};
        int code = pthread_cond_timedwait(&_cond, &_mutex, &ts);
        ASSERT(code == 0 || code == ETIMEDOUT, "timed wait failed,error:%s",strerror(code));
    }
    
    void pthread_recursivelock::notify()
    {
        pthread_cond_signal(&_cond);
    }
    
    void pthread_recursivelock::notify_all()
    {
        pthread_cond_broadcast(&_cond);
    }
}