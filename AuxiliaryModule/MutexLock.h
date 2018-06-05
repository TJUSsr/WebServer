//
// Created by Monster on 2018/6/4.
//
#ifndef WEBSERVER_MUTEXLOCK_H
#define WEBSERVER_MUTEXLOCK_H

#include "noncopyable.h"
#include <pthread.h>
#include <cstdio>

namespace WebServer{
    //参考muduo实现锁的RAII
    class MutexLock: public noncopyable{
    public:
        MutexLock(){
            pthread_mutex_init(&mutex, NULL);
        }
        ~MutexLock(){
            //需要先加锁，再析构
            pthread_mutex_lock(&mutex);
            pthread_mutex_destroy(&mutex);
        }
        void lock(){
            pthread_mutex_lock(&mutex);
        }
        void unlock(){
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_t* get(){
            return &mutex;
        }
    private:
        pthread_mutex_t mutex;
        //生命Condition类为友元类
        friend class Condition;
    };

    class MutexLockGuard: public noncopyable{
    public:
        //禁止隐式类型转换
        //MutexLockGuard类内有成员是引用，所以必须利用构造函数初始化列表进行初始化
        explicit MutexLockGuard(MutexLock& mutex_):mutex(mutex_){
            mutex.lock();
        }
        ~MutexLockGuard(){
            mutex.unlock();
        }
    private:
        MutexLock &mutex;
    };

}



#endif //WEBSERVER_MUTEXLOCK_H
