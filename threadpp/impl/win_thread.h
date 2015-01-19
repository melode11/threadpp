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
        struct win_context
        {
            void(*fp)(void*);
            void* context;
        } _context;
#if NO_CRT
        typedef DWORD handle_t;
#else
		typedef unsigned handle_t;
#endif
		static handle_t __stdcall win_fp_delegate(void* context);
        handle_t _thread_id;
        HANDLE _handle;
        win_thread(){};
        void operator=(const win_thread& t){};
        win_thread(const win_thread& t){};
    public:
        typedef void (*runnable)(void* ctx);
        typedef unsigned int id_type;
        
        static id_type null_id();
        
        win_thread(runnable r,void* t);
        
        ~win_thread();
        void join();
        void detach();
        bool is_equal(const win_thread& t) const;
        id_type get_id() const;
        static id_type current_thread_id();
        static void sleep(unsigned long millisecs);
    };
}

#include "win_thread.hpp"
#endif /* defined(__threadpp__win_thread__) */
