//
// Created by Monster on 2018/6/5.
//

#ifndef WEBSERVER_CURRENTTHREAD_H
#define WEBSERVER_CURRENTTHREAD_H

#include <cstdint>

namespace WebServer{
    namespace CurrentThread{

        extern __thread int t_cachedTid;
        extern __thread char t_tidString[32];
        extern __thread int t_tidStringLength;
        extern __thread const char* t_threadName;

        void cacheTid();

        inline int tid(){
            if(t_cachedTid==0){
                cacheTid();
            }
            return t_cachedTid;
        }

        inline const char* tidString(){
            return t_tidString;
        }

        inline int tidStringLength(){
            return t_tidStringLength;
        }

        inline const char* name(){
            return t_threadName;
        }


    }
}

#endif //WEBSERVER_CURRENTTHREAD_H
