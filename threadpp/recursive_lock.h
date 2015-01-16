//
//  recursive_lock.h
//  threadpp
//
//  Created by Melo Yao on 1/16/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef threadpp_recursive_lock_h
#define threadpp_recursive_lock_h
#include "threadpp_assert.h"
namespace threadpp
{
    template <typename locktype,typename threadtype>
    class recursive_lock
    {
        locktype _lock;
        volatile threadtype::id_type _owner;
        volatile unsigned int _count;
    public:
        recursive_lock();
        void lock();
        void unlock();
        void wait();
        void wait(unsigned long millisecs);
        void notify();
        void notify_all();
    };
    
    template <typename locktype,typename threadtype>
    recursive_lock<locktype,threadtype>::recursive_lock():_owner(0),_count(0)
    {
    }
    
    template <typename locktype,typename threadtype>
    void recursive_lock<locktype,threadtype>::lock()
    {
        unsigned int tid = threadtype::current_thread_id();
        if(tid == _owner)
        {
            _count++;
        }
        else
        {
            _lock.lock();
            _owner = tid;
            _count=1;
        }
    }
    
    template <typename locktype,typename threadtype>
    void recursive_lock<locktype,threadtype>::unlock()
    {
        unsigned int tid = threadtype::current_thread_id();
        ASSERT(tid == _owner,"%s", "unlock failed,try to unlock not owned mutex");
        _count--;
        if (_count == 0) {
            _lock.unlock();
        }
    }
    
    template <typename locktype,typename threadtype>
    void recursive_lock<locktype,threadtype>::wait()
    {
        threadtype::id_type owner = _owner;
        unsigned count = _count;
        _owner = 0;
        _count = 0;
        _lock.wait();
        _owner = owner;
        _count = count;

    }
    
    template <typename locktype,typename threadtype>
    void recursive_lock<locktype,threadtype>::wait(unsigned long millisecs)
    {
        threadtype::id_type owner = _owner;
        unsigned count = _count;
        _owner = 0;
        _count = 0;
        _lock.wait(millisecs);
        _owner = owner;
        _count = count;
    }
    
    template <typename locktype,typename threadtype>
    void recursive_lock<locktype,threadtype>::notify()
    {
        _lock.notify();
    }
    
    template <typename locktype,typename threadtype>
    void recursive_lock<locktype,threadtype>::notify_all()
    {
        _lock.notify_all();
    }
}

#endif
