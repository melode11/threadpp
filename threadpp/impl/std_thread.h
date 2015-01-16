//
//  std_thread.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef __threadpp__std_thread__
#define __threadpp__std_thread__
#include <thread>

namespace threadpp
{
    class std_thread
    {
        std::thread _thread;
        std_thread(){};
        void operator=(const std_thread& t){};
        std_thread(const std_thread& t){};
    public:
        typedef std::thread::id id_type;
        
        typedef void (*runnable)(void* ctx);
        
        static id_type null_id;
        
        std_thread(runnable r,void* t);
        
        ~std_thread();
        void join();
        void detach();
        bool is_equal(const std_thread& t) const;
        id_type get_id() const;
        static id_type current_thread_id();
        static void sleep(unsigned long millisecs);
    };
}


#endif /* defined(__threadpp__std_thread__) */
