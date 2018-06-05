//
// Created by Monster on 2018/6/5.
//
#include "CountDownLatch.h"
namespace WebServer{
    CountDownLatch::CountDownLatch(int count):mutex_(),condition_(mutex_),count_(count) {}

    CountDownLatch::wait(){
        //注意此处容易写成 MutexLockGuard(mutex_)，这是错误的，此举会产生一个临时MutexLockGuard 之后被析构，无法达到加锁的目的
        MutexLockGuard lock(mutex_);
        while(count_>0)
            condition_.wait();
    }

    void CountDownLatch::countDown() {
        MutexLockGuard lock(mutex_);
        --count_;
        if(count_==0)
            condition_.notifAll();
    }
}
