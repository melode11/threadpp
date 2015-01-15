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
        typedef void (*runnable)(void* ctx);
        
        std_thread(runnable r,void* t);
        
        ~std_thread();
        void join();
        void detach();
        bool is_equal(const std_thread& t) const;
        static void sleep(unsigned long millisecs);
        static bool is_current_thread(const std_thread& t);
    };
}


#endif /* defined(__threadpp__std_thread__) */
