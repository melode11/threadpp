//
//  std_lock.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include "std_lock.h"
#include "../threadpp_assert.h"
using namespace std;

namespace threadpp{
    
    std_lock::std_lock():_mutex(),_cond()
    {
    }
    
    std_lock::~std_lock()
    {
    }
    
    void std_lock::lock()
    {
        _mutex.lock();
    }
    
    void std_lock::unlock()
    {
        _mutex.unlock();
    }
    
    void std_lock::wait()
    {
        _cond.wait(_mutex);
    }
    
    void std_lock::wait(unsigned long millisecs)
    {
        _cond.wait_for(_mutex, chrono::milliseconds(millisecs));
    }
    
    void std_lock::notify()
    {
        _cond.notify_one();
    }
    
    void std_lock::notify_all()
    {
        _cond.notify_all();
    }
}