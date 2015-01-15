//
//  std_recursivelock.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include "std_recursivelock.h"
#include "../threadpp_assert.h"
using namespace std;

namespace threadpp{
    
    std_recursivelock::std_recursivelock():_mutex(), _lock(_mutex),_cond()
    {
    }
    
    std_recursivelock::~std_recursivelock()
    {
    }
    
    void std_recursivelock::lock()
    {
        _lock.lock();
    }
    
    void std_recursivelock::unlock()
    {
        _lock.unlock();
    }
    
    void std_recursivelock::wait()
    {
        _cond.wait(_lock);
    }
    
    void std_recursivelock::wait(unsigned long millisecs)
    {
        _cond.wait_for(_lock, chrono::milliseconds(millisecs));
    }
    
    void std_recursivelock::notify()
    {
        _cond.notify_one();
    }
    
    void std_recursivelock::notify_all()
    {
        _cond.notify_all();
    }
}