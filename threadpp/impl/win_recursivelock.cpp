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
#include "stdio.h"
namespace threadpp{

	static inline void test_error(const char* title)
	{
		DWORD e = GetLastError();
		ASSERT(e==0,"%s failed,error:%d",title,e);
	}

    win_recursivelock::win_recursivelock():_owner(0),_count(0)
    {
		SetLastError(0);
        InitializeCriticalSection(&_mutex);
        InitializeConditionVariable(&_cond);
		test_error("init");
    }
    
    win_recursivelock::~win_recursivelock()
    {
        DeleteCriticalSection(&_mutex);
    }
    
    void win_recursivelock::lock()
    {
		SetLastError(0);
        unsigned int tid = win_thread::get_current_thread_id();
        if(tid == _owner)
        {
            _count++;
        }
        else
        {
            EnterCriticalSection(&_mutex);
            _owner =tid;
            _count=1;
			test_error("lock");
        }
    }
    
    void win_recursivelock::unlock()
    {
		SetLastError(0);
        unsigned int tid = win_thread::get_current_thread_id();
        ASSERT(tid == _owner,"%s", "unlock failed,try to unlock not owned mutex");
        _count--;
        if(_count == 0)
        {
            LeaveCriticalSection(&_mutex);
			test_error("unlock");
        }
    }
    
    void win_recursivelock::wait()
    {
		SetLastError(0);
		unsigned owner = _owner;
		unsigned count = _count;
		_owner = 0;
		_count = 0;
        SleepConditionVariableCS(&_cond,&_mutex,0xFFFFFFFF);
		_owner = owner;
		_count = count;
		test_error("wait");
    }
    
    void win_recursivelock::wait(unsigned long millisecs)
    {
		SetLastError(0);
		unsigned owner = _owner;
		unsigned count = _count;
		_owner = 0;
		_count = 0;
        SleepConditionVariableCS(&_cond,&_mutex,millisecs);
		_owner = owner;
		_count = count;
		DWORD e = GetLastError();
		ASSERT(e==0||e == ERROR_TIMEOUT,"timed wait failed,error:",e);
    }
    
    void win_recursivelock::notify()
    {
		SetLastError(0);
        WakeConditionVariable(&_cond);
		test_error("notify");
    }
    
    void win_recursivelock::notify_all()
    {
		SetLastError(0);
        WakeAllConditionVariable(&_cond);
		test_error("notify all");
    }
}