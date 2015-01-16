//
//  std_thread.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include "std_thread.h"
#include <functional>
using namespace std;
namespace threadpp
{
    std_thread::id_type std_thread::null_id;
    
    void* std_fp_delegate(std_thread::runnable r, void* context)
    {
        r(context);
        return nullptr;
    }
    
    std_thread::std_thread(runnable r,void* t):_thread(std::bind(std_fp_delegate,r,t))
    {
    }
    
    std_thread::~std_thread()
    {
        
    }
    
    void std_thread::join()
    {
        _thread.join();
    }
    
    void std_thread::detach()
    {
        _thread.detach();
    }
    
    bool std_thread::is_equal(const std_thread& t) const
    {
        return _thread.get_id() == t._thread.get_id();
    }
    
    std_thread::id_type std_thread::get_id() const
    {
        return _thread.get_id();
    }
    
    void std_thread::sleep(unsigned long millisecs)
    {
        this_thread::sleep_for(chrono::milliseconds(millisecs));
    }
    
    std_thread::id_type std_thread::current_thread_id()
    {
        return this_thread::get_id();
    }
}