//
//  std_thread.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//
#ifndef __threadpp__std_thread__hpp__
#define __threadpp__std_thread__hpp__
#include <functional>
#include <algorithm>
namespace threadpp
{
    inline std_thread::id_type std_thread::null_id()
    {
        return 0;
    }
    
    inline void* std_fp_delegate(std_thread::runnable r, void* context)
    {
        r(context);
        return nullptr;
    }
    
    inline std_thread::std_thread(runnable r,void* t):_thread(std::bind(std_fp_delegate,r,t))
    {
    }
    
    inline std_thread::~std_thread()
    {
        
    }
    
    inline void std_thread::join()
    {
        _thread.join();
    }
    
    inline void std_thread::detach()
    {
        _thread.detach();
    }
    
    inline bool std_thread::is_equal(const std_thread& t) const
    {
        return _thread.get_id() == t._thread.get_id();
    }
    
    inline std_thread::id_type std_thread::get_id() const
    {
        return std::hash<std::thread::id>()(_thread.get_id());
    }
    
    inline void std_thread::sleep(unsigned long millisecs)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecs));
    }
    
    inline std_thread::id_type std_thread::current_thread_id()
    {
        return std::hash<std::thread::id>()(std::this_thread::get_id());
    }
}
#endif