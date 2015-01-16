//
//  pthread_thread.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__pthread_thread__
#define __threadpp__pthread_thread__
#include <pthread.h>
namespace threadpp
{
    class pthread_thread
    {
        struct pthread_context
        {
            void(*fp)(void* context);
            void* context;
        } _context;
        
        pthread_t _thread;
        pthread_thread(){};
        void operator=(const pthread_thread& t){};
        pthread_thread(const pthread_thread& t){};
        static void* pthread_fp_delegate(void*);
    public:
        typedef void (*runnable)(void* ctx);
        typedef unsigned long long id_type;
        static id_type null_id;
        
        pthread_thread(runnable r,void* t);
        
//        pthread_thread(runnable r,void* t,float priority);
        
        ~pthread_thread();
        void join();
        void detach();
        bool is_equal(const pthread_thread& t) const;
        id_type get_id() const;
        static id_type current_thread_id();
        static void sleep(unsigned long millisecs);
    };
}

#endif /* defined(__threadpp__pthread_thread__) */
