//
//  win_recursivelock.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include "win_recursivelock.h"
#include "win_thread.h"
#include "../threadpp_assert.h"
namespace threadpp{
    win_recursivelock::win_recursivelock():_owner(0),_count(0)
    {
        InitializeCriticalSection(_mutex);
        InitializeConditionVariable(_cond);
    }
    
    win_recursivelock::~win_recursivelock()
    {
        DeleteCriticalSection(_mutex);
    }
    
    void win_recursivelock::lock()
    {
        unsigned int tid = win_thread::get_current_thread_id();
        if(tid == _owner)
        {
            _count++;
        }
        else
        {
            EnterCriticalSection(_mutex);
            _owner =tid;
            _count=1;
        }
    }
    
    void win_recursivelock::unlock()
    {
        unsigned int tid = win_thread::get_current_thread_id();
        ASSERT(tid == _owner,"%s", "unlock failed,try to unlock not owned mutex");
        _count--;
        if(_count == 0)
        {
            LeaveCriticalSection(_mutex);
        }
    }
    
    void win_recursivelock::wait()
    {
        SleepConditionVariableCS(_cond,_mutex,0xFFFFFFFF);
    }
    
    void win_recursivelock::wait(unsigned long millisecs)
    {
        SleepConditionVariableCS(_cond,_mutex,millisecs);
    }
    
    void win_recursivelock::notify()
    {
        WakeConditionVariable(_cond);
    }
    
    void win_recursivelock::notify_all()
    {
        WakeAllConditionVariable(_cond);
    }
}