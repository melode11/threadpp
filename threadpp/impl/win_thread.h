//
//  win_thread.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__win_thread__
#define __threadpp__win_thread__

#include <windows.h>

namespace threadpp
{
    class win_thread
    {
        unsigned int _thread_id;
        HANDLE _handle;
        win_thread(){};
        void operator=(const win_thread& t){};
        win_thread(const win_thread& t){};
    public:
        typedef unsigned __stdcall (*runnable)(void* ctx);
        
        win_thread(runnable r,void* t);
        
        ~win_thread();
        void join();
        void detach();
        bool is_equal(const win_thread& t) const;
        static void sleep(unsigned long millisecs);
        static bool is_current_thread(const win_thread& t);
        static unsigned int get_current_thread_id();
    };
}

#endif /* defined(__threadpp__win_thread__) */
