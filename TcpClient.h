#ifndef _TCP_CLIENT_H__
#define _TCP_CLIENT_H__

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include "AsyncSocket.h"
#include "AsyncEpoller.h"
#include "RawBuffer.h"
#include "third.pb.h"
#include "NetMsg.h"

using namespace std;

#define RECV_MAXLEN (2048)
#define PACK_MAXLEN (4096)

class CTcpClient : public CAsyncSocket
{
public:
    CTcpClient(CAsyncEpoller *epoller);
    virtual ~CTcpClient();

    /**
     * 消息内容具体处理
     */
    void dispatch(const MsgHead &header, const char *ptr, const int32_t len);

    /**
     * 连接检查器
     */
    void connectChecker();

protected:
    /**
     * 读取事件通知
     */
    void intputNotify();

    /**
     * 写入事件通知
     */
    void outputNotify();

    /**
     * 异常事件通知
     */
    void errorNotify();

    /**
     * 定时器事件通知
     */
    void timerNotify();

public:
    /**
     * 建立连接
     */
    int Connect(const char *addr, const uint16_t port, const int32_t timeout = 5000);

    /**
     * 建立连接
     */
    int Connect(const int32_t timeout = 5000);

    /**
     * 重连服务
     */
    int Reconnect();

    /**
     * 发送数据
     */
    int Send(const char *vptr, const int32_t len);

    /**
     * 关闭连接
     */
    void Close();

    /**
     * 非阻塞方式
     */
    int SetNonblocking(const int32_t fd);

    /**
     * 插入事件管理队列
     */
    int AddEpoller(int32_t fd);

private:
    /**
     * 接收事件处理
     */
    int Recv();

    /**
     * 发送事件处理
     */
    int Send();

    /**
     * 异常事件处理
     */
    int Error();

    /**
     * 消息处理分发
     */
    int Dispatch();

public:
    /**
     * 连接注册消息
     */
    int NodeLoginMsg();

    /**
     * 连接心跳消息
     */
    int NodeKeepAliveMsg();

    /**
     * 查询数据报告
     */
    int NodeDataReportMsg(const long uid);

    /**
     * 行为决策结果
     */
    int NodeAICalcMsg(const long uid, const string roomid, const int round);

    /**
     * 转发消息给平台
     */
    int TransmitToPlatform(const long uid, const int type, const string &msg);

public:
    /**
     * 注册处理
     */
    int OnNodeLogin(const MsgHead &header, const char *ptr, const int32_t len);

    /**
    * 心跳处理
    */
    int OnNodeKeepAlive(const MsgHead &header, const char *ptr, const int32_t len);

    /**
    * 机器决策
    */
    int OnNodeAIDecide(const MsgHead &header, const char *ptr, const int32_t len);

    /**
    * 分析报告
    */
    int OnNodeAIReport(const MsgHead &header, const char *ptr, const int32_t len);

private:
    /**
     *数据接收缓存区
     */
    char _buffer[RECV_MAXLEN];
    /**
     * 接收缓存队列
     */
    CRawBuffer *_recvBuffer;
    /**
     * 发送缓存队列
     */
    CRawBuffer *_sendBuffer;

public:
    //获取节点标识
    const int32_t getSvrID();
    //设置节点标识
    void setSvrID(const int32_t id);
    //获取主机地址
    const char *getSvrAddr();
    //设置主机地址
    void setSvrAddr(const char *addr);
    //获取主机端口
    const int16_t getSvrPort();
    //设置主机端口
    void setSvrPort(const int16_t port);
    //获取连接密钥
    const char *getSvrToken();
    //设置连接密钥
    void setSvrToken(const char *token);
    //是否已经重连
    bool isConnected();

private:
    /**
     * 连接密钥
     */
    char _token[512];
    /**
     * 连接端标识
     */
    int32_t _svrid;
    /**
     * 本地标识
     */
    uint64_t _connid;
    /**
     * 最大数据包
     */
    char _packet[PACK_MAXLEN];
    /**
     * 服务器地址
     */
    char _svraddr[32];
    /**
     * 服务器端口
     */
    int16_t _svrport;
    /**
     * 服务器超时秒数
     */
    uint32_t _svrtimeout;
    /**
     * 是否断开重连
     */
    bool _reconnect;
    /**
     * 是否已经连接
     */
    bool _connected;
    /**
     * PB文本输出开关
     */
    bool _textFormatPrint;
};

typedef CTcpClient *CTcpClientPtr;

#endif

