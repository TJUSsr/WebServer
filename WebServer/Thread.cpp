//
// Created by Monster on 2018/6/5.
//
#include "Thread.h"
#include "CurrentThread.h"
#include <memory>
#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <cassert>


namespace WebServer{


    //__thread是GCC内置的线程局部存储设施，存取效率可以和全局变量相比，
    //__thread变量每一个线程有一份独立的实体，各个线程的值互不干扰，
    //可以用来修饰POD类型，不能修饰class类型
    namespace CurrentThread{
        __thread int t_cachedTid=0;
        __thread char t_tidString[32];
        __thread int t_tidStringLength=6;
        __thread const char* t_threadName="default";
    }

    pid_t gettid(){
        return static_cast<pid_t>(::syscall(SYS_gettid));
    }

    void CurrentThread::cacheTid() {
        if(t_cachedTid==0){
            t_cachedTid=gettid();
            t_tidStringLength=snprintf(t_tidString,sizeof(t_tidString),"%5d",t_cachedTid);
        }
    }



    struct ThreadData{
        typedef Thread::ThreadFunc ThreadFunc;
        ThreadFunc func_;
        std::string name_;
        pid_t* tid_;
        CountDownLatch* latch_;

        ThreadData(const ThreadFunc& func, const std::string& name, pid_t* tid, CountDownLatch* latch):func_(func),name_(name),tid_(tid),latch_(latch){}

        void runInThread(){
            //tid_所指向的pid_t为当前线程的SYS_gettid
            *tid_= CurrentThread::tid();
            tid_=NULL;
            latch_->countDown();
            latch_=NULL;

            CurrentThread::t_threadName=name_.empty()?"Thread":name_.c_str();
            pthread_setname_np(CurrentThread::t_threadName);

            func_();
            CurrentThread::t_threadName="finished";
        }

    };

    void *startThread(void* obj){
        auto data=std::make_shared(static_cast<ThreadData*>(obj));
        data->runInThread();
        return NULL;
    }


    Thread::Thread(const ThreadFunc & func, const std::string &name):started_(false),joined_(false),pthreadID_(0),tid_(0),func_(func),name_(name),latch_(1) {
        setDefaultName();
    }

    Thread::~Thread() {
        if(started_&&~joined_)
            pthread_detach(pthreadID_);
    }

    void Thread::setDefaultName() {
        if(name_.empty()){
            char buf[32];
            snprintf(buf,sizeof(buf),"Thread");
            name_=buf;
        }
    }

    void Thread::start() {
        assert(!started_);
        started_=true;
        auto data=std::make_shared(ThreadData(func_,name_,&tid_,&latch_));
        if(pthread_create(&pthreadID_,NULL,&startThread,data.get())){
            started_= false;
        }else{
            latch_.wait();
            assert(tid_>0);
        }
    }

    int Thread::join(){
        assert(started_);
        assert(!joined_);
        joined_=true;
        return pthread_join(pthreadID_,NULL);
    }

}

