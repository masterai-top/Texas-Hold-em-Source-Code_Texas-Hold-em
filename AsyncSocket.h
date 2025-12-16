#ifndef _ASYNC_SOCKET_H__
#define _ASYNC_SOCKET_H__

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "AsyncEpoller.h"

class CAsyncEpoller;
class CAsyncSocket
{
public:
    CAsyncSocket(CAsyncEpoller *epoller);
    virtual ~CAsyncSocket();

    /**
     * 读取事件通知
     */
    virtual void intputNotify() = 0;

    /**
     * 写入事件通知
     */
    virtual void outputNotify() = 0;

    /**
     * 异常事件通知
     */
    virtual void errorNotify() = 0;

    /**
    * 定时器事件通知
    */
    virtual void timerNotify() = 0;

    /**
     * 连接心跳处理
     */
    virtual void connectChecker() = 0;

protected:
    /**
     * 禁止读取事件监听
     */
    bool disableInput();

    /**
     * 开启读取事件监听
     */
    bool enableInput();

    /**
     * 禁止写入事件监听
     */
    bool disableOutput();

    /**
     * 开启写入事件监听
     */
    bool enableOutput();

    /**
     * 加入事件监听队列
     */
    bool addEpoller();

    /**
     * 移除事件监听队列
     */
    bool delEpoller();

    /**
     * 事件管理对象
     */
    CAsyncEpoller *epoller();

    /**
     * 设置事件句柄
     */
    void setFd(int32_t fd);

public:
    /**
    * 获取事件句柄
    */
    int32_t getFd();

    /**
     * 事件结构对象
     */
    struct epoll_event *getEvents();

    /**
     * 获取上次交互时间
     */
    uint64_t getLastAccessTime();

    /**
     * 设置上次交互时间
     */
    void setLastAccessTime(uint64_t ts);

    /**
     * 获取连接标识
     */
    bool isConnected();

    /**
     * 设备连接标识
     */
    void setConnected(bool flags);

private:
    /**
     * 事件句柄
     */
    int32_t _fd;
    /**
     * 事件操作结构
     */
    struct epoll_event _ev;
    /**
     * 事件管理对象
     */
    CAsyncEpoller *_epoller;
    /**
     * 上次通知时间
     */
    uint64_t _lastAccessTime;
    /**
     * 是否已经连接
     */
    bool _connected;
};

#endif

