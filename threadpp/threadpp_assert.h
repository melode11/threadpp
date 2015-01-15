//
//  defines.h
//  threadpp
//
//  Created by Melo Yao on 1/15/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#ifndef threadpp_assert_h
#define threadpp_assert_h

//forward VC++ DEBUG symbol.
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG _DEBUG
#endif

#if DEBUG //assertions
#ifdef __cplusplus
#include <cassert>
#include <cstdio>
#else
#include <assert.h>
#include <stdio.h>
#endif
#define ASSERT0(__cond__) assert(__cond__)
#define ASSERT(__cond__,__msg__,...) \
do {if(!(__cond__)){printf(__msg__,__VA_ARGS__);printf("\n");assert(false);}}while(0)
#else
#define ASSERT0(__cond__)
#define ASSERT(__cond__,__msg__,...)
#endif //assertions

#endif
