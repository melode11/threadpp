//
//  threadpp.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef threadpp_threadpp_h
#define threadpp_threadpp_h

#if __posix || __APPLE__ || __linux
#include "impl/pthread_thread.h"
#include "impl/pthread_recursivelock.h"
namespace threadpp
{
    typedef pthread_thread thread;
    typedef pthread_recursivelock recursivelock;
}
#elif defined(WIN32)
#include "impl/win_thread.h"
#include "impl/win_recursivelock.h"
namespace threadpp
{
    typedef win_thread thread;
    typedef win_recursivelock recursivelock;
}
#elif __cplusplus>=201103L
#include "impl/std_thread.h"
#include "impl/std_recursivelock.h"
namespace threadpp
{
    typedef std_thread thread;
    typedef std_recursivelock recursivelock;
}
#endif
#endif
