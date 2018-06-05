//
// Created by Monster on 2018/6/4.
//

#ifndef WEBSERVER_THREAD_H
#define WEBSERVER_THREAD_H

#include "../AuxiliaryModule/CountDownLatch.h"
#include "../AuxiliaryModule/noncopyable.h"
#include <functional>
#include <memory>
#include <pthread.h>
#include <string>
#include <sys/syscall.h>
#include <unistd.h>

namespace WebServer{
    class Thread: public noncopyable{
    public:
        //std::function是可调用对象的包装器
        //ThreadFunc是一个类，他可以实例化一个对象，接收0个参数，返回void类型
        typedef std::function<void()> ThreadFunc;
        explicit Thread(const ThreadFunc&, const std::string& name=std::string());
        ~Thread();

        void start();
        int join();
        bool started() const{return started_;}
        pid_t tid() const {return tid_;}
        const std::string& name() const {return name_;}

    private:
        void setDefaultName();
        bool started_;
        bool joined_;
        pthread_t pthreadID_;
        pid_t tid_;
        ThreadFunc func_;
        std::string name_;
        CountDownLatch latch_;
    };
}

#endif //WEBSERVER_THREAD_H
