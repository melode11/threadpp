//
//  pthread_thread.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include "pthread_thread.h"
#include <errno.h>
#include "../threadpp_assert.h"
#include <cstring>
#include <cmath>
#include <unistd.h>
namespace threadpp
{
    
    pthread_thread::pthread_thread(runnable r,void* t)
    {
        pthread_attr_t tattr;
        pthread_attr_init(&tattr);
        int code = pthread_create(&_thread, &tattr, r, t);
        ASSERT(code==0,"create thread failed,error:%s",strerror(code));
        pthread_attr_destroy(&tattr);
    }
    
    pthread_thread::pthread_thread(runnable r,void* t,float priority)
    {
        
        pthread_attr_t tattr;
        pthread_attr_init(&tattr);
        struct sched_param schp;
        int policy = SCHED_FIFO;
        pthread_attr_getschedpolicy(&tattr, &policy);
        pthread_attr_getschedparam(&tattr, &schp);
        float pr =fminf(1.0f,fmaxf(0.0f, priority));
        schp.sched_priority = sched_get_priority_min(policy) + pr*(sched_get_priority_max(policy) - sched_get_priority_min(policy));
        pthread_attr_setschedparam(&tattr, &schp);
        int code = pthread_create(&_thread, &tattr, r, t);
        ASSERT(code==0,"create thread failed,error:%s",strerror(code));
        pthread_attr_destroy(&tattr);
    }
    
    pthread_thread::~pthread_thread()
    {

    }
    
    void pthread_thread::join()
    {
        void* ret = NULL;
        int code = pthread_join(_thread, &ret);
        ASSERT(code==0,"join thread failed,error:%s",strerror(code));
    }
    
    void pthread_thread::detach()
    {
        int code = pthread_detach(_thread);
        ASSERT(code==0,"join thread failed,error:%s",strerror(code));

    }
    
    bool pthread_thread::is_equal(const pthread_thread& t) const
    {
        return pthread_equal(_thread, t._thread);
    }
    
    void pthread_thread::sleep(unsigned long millisecs)
    {
        usleep((useconds_t)millisecs*1000);
    }
    
    bool pthread_thread::is_current_thread(const pthread_thread& t)
    {
        return pthread_equal(pthread_self(),t._thread);
    }
}