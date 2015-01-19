# threadpp
Light-weight cross-platform thread/mutex implementations including win32, win8,linux,macOS,iOS,android.
## Sample:
>\#include "threadpp.h"
>
>using namespace threadpp;
>
>recursivelock l;
>
>void thread_callback(void* context)
>{
>
>    l.lock();
>
>    l.wait();//wait-notify paradigm,will be wake up by main in 3 seconds
>
>    printf("hello from thread:%llu\n",thread::current_thread_id());
>
>    l.unlock();
>
>}
>
>
>int main(int argc,const char** argv)
>{
>
>    thread t(thread_callback,NULL);
>
>    thread::sleep(3000);
>
>    l.notify_all();//wait-notify paradigm.
>
>    t.join();
>
>}
