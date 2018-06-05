//
// Created by Monster on 2018/6/6.
//

#ifndef WEBSERVER_HTTPDATA_H
#define WEBSERVER_HTTPDATA_H

#include "Timer.h"
#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <functional>
#include <unistd.h>

namespace WebServer{
    class EventLoop;
    class TimerNode;
    class Channel;

    enum ProcessState{
        STATE_PARSE_URI=1,
        STATE_PARSE_HEADERS,
        STATE_RECV_BODY,
        STATE_ANALYSIS,
        STATE_FINISH
    };
    
    enum URIState
    {
        PARSE_URI_AGAIN = 1,
        PARSE_URI_ERROR,
        PARSE_URI_SUCCESS,
    };

    enum HeaderState
    {
        PARSE_HEADER_SUCCESS = 1,
        PARSE_HEADER_AGAIN,
        PARSE_HEADER_ERROR
    };

    enum AnalysisState
    {
        ANALYSIS_SUCCESS = 1,
        ANALYSIS_ERROR
    };

    enum ParseState
    {
        H_START = 0,
        H_KEY,
        H_COLON,
        H_SPACES_AFTER_COLON,
        H_VALUE,
        H_CR,
        H_LF,
        H_END_CR,
        H_END_LF
    };

    enum ConnectionState
    {
        H_CONNECTED = 0,
        H_DISCONNECTING,
        H_DISCONNECTED
    };

    enum HttpMethod
    {
        METHOD_POST = 1,
        METHOD_GET,
        METHOD_HEAD
    };

    enum HttpVersion
    {
        HTTP_10 = 1,
        HTTP_11
    };

}

#endif //WEBSERVER_HTTPDATA_H
