//
//  threadpp.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef threadpp_threadpp_h
#define threadpp_threadpp_h
#include "recursive_lock.h"
#if __posix || __APPLE__ || __linux
#include "impl/pthread_thread.h"
#include "impl/pthread_lock.h"
namespace threadpp
{
    typedef pthread_thread thread;
    typedef pthread_lock lock;
    typedef recursive_lock<pthread_lock, pthread_thread> recursivelock;
}
#elif defined(WIN32)
#include "impl/win_thread.h"
#include "impl/win_lock.h"
namespace threadpp
{
    typedef win_thread thread;
    typedef win_lock lock;
    typedef recursive_lock<win_lock, win_thread> recursivelock;
}
#elif __cplusplus>=201103L
#include "impl/std_thread.h"
#include "impl/std_lock.h"
namespace threadpp
{
    typedef std_thread thread;
    typedef std_lock lock;
    typedef recursive_lock<std_lock, std_thread> recursivelock;
}
#endif
#endif
