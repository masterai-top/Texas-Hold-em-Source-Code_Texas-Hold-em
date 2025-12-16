#ifndef _ASYNC_EPOLLER_H__
#define _ASYNC_EPOLLER_H__

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <vector>

using namespace std;

class CAsyncSocket;
class CTcpClient;
class CAsyncEpoller
{
public:
    CAsyncEpoller();
    virtual ~CAsyncEpoller();

    /**
     * 初始化
     * @param  nMaxClients [最大监听用户连接数]
     * @return             [description]
     */
    bool init(int32_t nMaxClients);

    /**
     * 主循环
     * @return [description]
     */
    bool loop();

    /**
     * 清理
     * @return [description]
     */
    bool final();

    /**
     * 管理对象名柄
     * @return [description]
     */
    int32_t getEpfd();

    /**
     * 添加到件监听队列
     */
    bool addEpoller(CAsyncSocket *as);

    /**
     * 移除事件监听队列
     */
    bool delEpoller(CAsyncSocket *as);

    /**
     * 开启本地监听操作
     */
    bool openListen(const int16_t port);

    /**
     * 连接超时检查
     */
    bool checkConnections();

private:
    /**
     * 管理对象句柄
     */
    int32_t _epfd;
    /**
     * 连接监听句柄
     */
    int32_t _listenfd;
    /**
     * 本地连接列表
     */
    std::map<int32_t, CAsyncSocket *> _connMap;
    /**
     * 连接检查队列
     */
    std::deque<CAsyncSocket *> _checkDeque;
};

#endif

