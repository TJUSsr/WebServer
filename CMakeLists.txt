#制定Cmake最低版本
cmake_minimum_required(VERSION 3.10)
#工程的名字SsrSTL
project(WebServer)
set(CMAKE_CXX_STANDARD 11)
#设置可执行文件生成位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
include_directories(${PROJET_SOURCE_DIR})

if(WIN32 AND NOT MINGW)
    message("WIN32 AND NOT MINGW")
elseif(WIN32 AND MINGW)
    message("MINGW AND MINGW")
elseif(UNIX AND NOT ANDROID)
    message("UNIX AND NOT ANDROID")
elseif(ANDROID)
    message("ANDROID")
endif()

set(WebServer main.cpp WebServer/Channel.h WebServer/Epoll.h WebServer/EventLoop.h WebServer/EventLoopThread.h WebServer/EventThreadPool.h WebServer/HttpData.h WebServer/Server.h WebServer/ThreadPool.h AuxiliaryModule/Timer.h AuxiliaryModule/Util.h AuxiliaryModule/Config.h ServerLog/AsyncLogging.h ServerLog/FileUtil.h ServerLog/LogStream.h ServerLog/Logging.h AuxiliaryModule/Condition.h AuxiliaryModule/CountDownLatch.h AuxiliaryModule/CurrentThread.h ServerLog/LogFile.h AuxiliaryModule/MutexLock.h WebServer/Thread.h AuxiliaryModule/noncopyable.h AuxiliaryModule/CountDownLatch.cpp WebServer/Thread.cpp WebServer/CurrentThread.h AuxiliaryModule/Timer.cpp AuxiliaryModule/HttpData.h)
#生成可执行文件
add_executable(WebServer_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} ${WebServer})
if(UNIX AND NOT ANDROID)
    find_package(Threads)
    target_link_libraries (WebServer_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} ${CMAKE_THREAD_LIBS_INIT})
elseif(WIN32 AND MINGW)
    find_package(psapi)
    target_link_libraries (WebServer_${CMAKE_BUILD_TYPE}_${CMAKE_CXX_PLATFORM_ID} psapi)
endif()