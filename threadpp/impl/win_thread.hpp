//
//  win_thread.cpp
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//
#ifndef __threadpp__win_thread__hpp__
#define __threadpp__win_thread__hpp__

#include "../threadpp_assert.h"
#if NO_CRT
#else
#include <process.h>
#endif
namespace threadpp
{

    inline win_thread::id_type win_thread::null_id()
    {
        return 0;
    }
    
	inline win_thread::handle_t win_thread::win_fp_delegate(void *context)
    {
        win_context* wctx = static_cast<win_context*>(context);
        wctx->fp(wctx->context);
        return 0;
    }
    
    inline win_thread::win_thread(runnable r,void* t)
    {
        _context.fp = r;
        _context.context = t;
#if NO_CRT
		_handle = CreateThread(NULL,NULL,win_thread::win_fp_delegate,&_context,0,&_thread_id);
#else
		_handle = (HANDLE)_beginthreadex(NULL,0,win_thread::win_fp_delegate,&_context,0,&_thread_id);
#endif		
    }
    
    inline win_thread::~win_thread()
    {
        ASSERT(_handle == 0,"%s","must join or detach a thread before destructing it");
    }
    
    inline void win_thread::join()
    {
        unsigned code = WaitForSingleObject(_handle,0xFFFFFFFF);
        CloseHandle(_handle);
        _handle = 0;
        ASSERT(code == WAIT_OBJECT_0 || code == WAIT_ABANDONED, "failed to join,error:%d",code);
    }
    
    inline void win_thread::detach()
    {
		CloseHandle(_handle);
        _handle = 0;
    }
    
    inline bool win_thread::is_equal(const win_thread& t) const
    {
        return _thread_id == t._thread_id;
    }
    
    inline void win_thread::sleep(unsigned long millisecs)
    {
		Sleep(millisecs);
    }
    
	inline win_thread::id_type win_thread::get_id() const
	{
		return static_cast<unsigned int>(_thread_id);
	}

	inline win_thread::id_type win_thread::current_thread_id()
	{
		return  static_cast<unsigned int>(GetCurrentThreadId());
	}
}
#endif