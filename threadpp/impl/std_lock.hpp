//
//  std_lock.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//
#ifndef __threadpp__std_lock__hpp__
#define __threadpp__std_lock__hpp__
#include "../threadpp_assert.h"

namespace threadpp{
    
    inline std_lock::std_lock():_mutex(),_cond()
    {
    }
    
    inline std_lock::~std_lock()
    {
    }
    
    inline void std_lock::lock()
    {
        _mutex.lock();
    }
    
    inline void std_lock::unlock()
    {
        _mutex.unlock();
    }
    
    inline void std_lock::wait()
    {
        _cond.wait(_mutex);
    }
    
    inline void std_lock::wait(unsigned long millisecs)
    {
        _cond.wait_for(_mutex, std::chrono::milliseconds(millisecs));
    }
    
    inline void std_lock::notify()
    {
        _cond.notify_one();
    }
    
    inline void std_lock::notify_all()
    {
        _cond.notify_all();
    }
}
#endif