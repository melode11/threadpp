//
//  pthread_lock.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include "pthread_lock.h"
#include "../threadpp_assert.h"
#include <errno.h>
#include <cstring>

#include <sys/time.h>

void timespec_for(struct timespec* t,unsigned long millisecs) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
//    t->tv_sec = tv.tv_sec;
    t->tv_nsec = tv.tv_usec*1000 + millisecs*1000000;
    t->tv_sec = tv.tv_sec + (t->tv_nsec/1000000000);
    t->tv_nsec = t->tv_nsec%1000000000;
}

namespace threadpp{
    pthread_lock::pthread_lock()
    {
        _mutex = PTHREAD_MUTEX_INITIALIZER;
        _cond = PTHREAD_COND_INITIALIZER;
    }
    
    pthread_lock::~pthread_lock()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }
    
    void pthread_lock::lock()
    {
        int code = pthread_mutex_lock(&_mutex);
        ASSERT(code == 0, "lock failed,error:%s",strerror(code));
    }
    
    void pthread_lock::unlock()
    {
        int code = pthread_mutex_unlock(&_mutex);
        ASSERT(code == 0, "unlock failed,error:%s",strerror(code));
    }
    
    void pthread_lock::wait()
    {
        int code = pthread_cond_wait(&_cond, &_mutex);
        ASSERT(code == 0 || code == ETIMEDOUT, "wait failed,error:%s",strerror(code));
    }
    
    void pthread_lock::wait(unsigned long millisecs)
    {
        struct timespec ts;
        timespec_for(&ts,millisecs);
        int code = pthread_cond_timedwait(&_cond, &_mutex, &ts);
        ASSERT(code == 0 || code == ETIMEDOUT, "timed wait failed,error:%s",strerror(code));
    }
    
    void pthread_lock::notify()
    {
        pthread_cond_signal(&_cond);
    }
    
    void pthread_lock::notify_all()
    {
        pthread_cond_broadcast(&_cond);
    }
}