//
// Created by Monster on 2018/6/4.
//

#ifndef WEBSERVER_TIMER_H
#define WEBSERVER_TIMER_H

#include "MutexLock.h"
#include "../WebServer/HttpData.h"

#include <unistd.h>
#include <memory>
#include <queue>
#include <deque>

namespace WebServer{
    class HttpData;

    class TimerNode{
    public:
        //timeout单位应是毫秒
        TimerNode(std::shared_ptr<HttpData> requestData, int timeout);
        ~TimerNode();
        TimerNode(TimerNode& tn);

        void update(int timeout);
        bool isValid();
        void clearReq();
        void setDeleted(){deleted_=true;}
        bool isDeleted() const { return deleted_;}
        size_t getExpTime() const {return expiredTime_;}

    private:
        bool deleted_;
        size_t expiredTime_;
        std::shared_ptr<HttpData> SPHttpData;
    };

    //定义了一个仿函数，实现大于比较运算
    struct TimerCmp{
        bool operator()(std::shared_ptr<TimerNode>& lhs, std::shared_ptr<TimerNode>& rhs) const{
            return lhs->getExpTime()>rhs->getExpTime();
        }
    };

    class TimerManager{
    public:
        TimerManager();
        ~TimerManager();
        void addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout);
        void handleExpiredEvent();

    private:
        typedef std::shared_ptr<TimerNode> SPTimerNode;
        std::priority_queue<SPTimerNode,std::deque<SPTimerNode>,TimerCmp> timerNodeQueue;
    };

}


#endif //WEBSERVER_TIMER_H
