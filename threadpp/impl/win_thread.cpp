//
//  win_thread.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include "win_thread.h"
#include "../threadpp_assert.h"
namespace threadpp
{
    unsigned win_thread::win_fp_delegate(void *context)
    {
        win_context* wctx = static_cast<win_context*>(context);
        wctx->fp(wctx->context);
        return 0;
    }
    
    win_thread::win_thread(runnable r,void* t)
    {
        _context.fp = r;
        _context.context = t;
        _handle = _beginthreadex(NULL,0,win_thread::win_fp_delegate,&_context,0,&_thread_id);
    }
    
    win_thread::~win_thread()
    {
        
    }
    
    void win_thread::join()
    {
        unsigned code = WaitForSingleObject(_handle,0xFFFFFFFF);
        CloseHandle(_handle);
        _handle = 0;
        ASSERT(code == WAIT_OBJECT_0 || code == WAIT_ABANDONED, "failed to join,error:%d",code);
    }
    
    void win_thread::detach()
    {

    }
    
    bool win_thread::is_equal(const win_thread& t) const
    {
        return _thread_id == t._thread_id;
    }
    
    void win_thread::sleep(unsigned long millisecs)
    {
        
    }
    
    bool win_thread::is_current_thread(const win_thread& t)
    {

    }
}