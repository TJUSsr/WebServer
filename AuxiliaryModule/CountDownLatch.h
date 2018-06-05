//
// Created by Monster on 2018/6/4.
//

#ifndef WEBSERVER_COUNTDOWNLATCH_H
#define WEBSERVER_COUNTDOWNLATCH_H

#include "Condition.h"
#include "MutexLock.h"
#include "noncopyable.h"

namespace WebServer{
    class CountDownLatch: public noncopyable{
    public:
        explicit CountDownLatch(int count);
        void wait();
        void countDown();
    private:
        //mutable表示该变量是可变的，即使CountDownLatch是常量
        mutable MutexLock mutex_;
        Condition condition_;
        int count_;
    };
}

#endif //WEBSERVER_COUNTDOWNLATCH_H
