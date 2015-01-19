//
//  main.cpp
//  testthreadpp
//
//  Created by Melo Yao on 1/16/15.
//  Copyright (c) 2015 Melo Yao. All rights reserved.
//

#include <iostream>
#include "threadpp.h"

using namespace threadpp;
recursivelock l;
int global_int = 0;

void runthread(void* context)
{
    l.lock();
        global_int++;
    l.wait(5000);
    l.unlock();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    thread* ths[10];
    for (int i = 0; i<10; ++i) {
        ths[i] = new thread(runthread,NULL);
    }
    for (int i = 0; i<10; ++i) {
        ths[i]->join();
        delete ths[i];
    }
    
    std::cout << "int:"<<global_int<<std::endl;
    return 0;
}
