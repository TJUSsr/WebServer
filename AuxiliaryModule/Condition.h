//
// Created by Monster on 2018/6/4.
//

#ifndef WEBSERVER_CONDITION_H
#define WEBSERVER_CONDITION_H

#include "noncopyable.h"
#include "MutexLock.h"
#include <pthread.h>
#include <cerrno>
#include <cstdint>
#include <ctime>

namespace WebServer{
    /*
     * 构造自己的条件变量类 Condition
     * Condition需要结合mutex来进行设计
     */
    class Condition:public noncopyable{
    public:
        //禁止隐式类型转换，由于有成员变量为引用，所以需要利用构造函数初始化列表进行初始化
        explicit Condition(MutexLock& mutex_):mutex(mutex_){
            pthread_cond_init(&cond,NULL);
        }
        ~Condition(){
            pthread_cond_destroy(&cond);
        }
        void wait(){
            pthread_cond_wait(&cond,mutex.get());
        }
        void notify(){
            pthread_cond_signal(&cond);
        }
        void notifAll(){
            pthread_cond_broadcast(&cond);
        }
        //输入秒，转换为pthread_cond_timedwait接受的时间参数，并返回是否超时
        //注意返回值为一个布尔量
        bool waitForSeconds(int seconds){
            struct timespec abstime;
            clock_gettime(CLOCK_REALTIME,&abstime);
            abstime.tv_sec+= static_cast<time_t>(seconds);
            return ETIMEDOUT==pthread_cond_timedwait(&cond,mutex.get(),&abstime);
        }
    private:
        MutexLock& mutex;
        pthread_cond_t cond;
    };
}

#endif //WEBSERVER_CONDITION_H
