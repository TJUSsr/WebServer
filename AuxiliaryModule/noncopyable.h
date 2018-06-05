//
// Created by Monster on 2018/6/4.
//

#ifndef WEBSERVER_NONCOPYABLE_H
#define WEBSERVER_NONCOPYABLE_H

namespace WebServer{
    /*
     * 构造一个noncopyable类，之后禁止拷贝的函数均可以继承自该类
     * 子类调用复制构造函数或者赋值运算符时，需要调用基类的复制构造函数或者赋值运算符
     * 此时基类的复制构造函数，赋值运算符均为似有成员函数，所以子类无法调用，
     * 子类便无法实现复制或者赋值
     */
    class noncopyable{
    protected:
        noncopyable(){}
        ~noncopyable(){}
    private:
        noncopyable(const noncopyable&);
        const noncopyable& operator=(const noncopyable&);
    };
}

#endif //WEBSERVER_NONCOPYABLE_H
