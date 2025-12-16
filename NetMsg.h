#ifndef __NET_MSG_HEAD_H__
#define __NET_MSG_HEAD_H__

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
#include <arpa/inet.h>
#include "ThirdLog.h"

using namespace std;

#define HEAD_LEN  (20)

#pragma pack(push, 1)

extern uint64_t htonl64(uint64_t host64);
extern uint64_t ntohl64(uint64_t net64);

typedef struct MsgHead
{
    uint32_t  iLen;
    uint32_t  iCmd;
    uint64_t  lUid;
    uint32_t  iErr;
    // uint64_t  iSeq;
    MsgHead()
    {
        memset(this, 0, sizeof(MsgHead));
    }

    MsgHead(uint32_t len, uint32_t cmd, uint64_t uid, uint32_t err, uint64_t seq)
    {
        iLen  = len;
        iCmd  = cmd;
        lUid  = uid;
        iErr  = err;
        // iSeq  = seq;
    }

    bool Unpack(const char *pData, size_t nLen)
    {
        if (!pData || nLen < sizeof(MsgHead))
            return false;

        iLen = ntohl(((MsgHead *)(pData))->iLen);
        iCmd = ntohl(((MsgHead *)(pData))->iCmd);
        lUid = ntohl64(((MsgHead *)(pData))->lUid);
        iErr = ntohl(((MsgHead *)(pData))->iErr);
        // iSeq = ntohl64(((MsgHead *)(pData))->iSeq);
        return true;
    }

    bool Pack(char *pData, const size_t nLen)
    {
        if (!pData || nLen < sizeof(MsgHead))
            return false;

        auto pHead = (MsgHead *)pData;
        pHead->iLen = htonl(iLen);
        pHead->iCmd = htonl(iCmd);
        pHead->lUid = htonl64(lUid);
        pHead->iErr = htonl(iErr);
        // pHead->iSeq = htonl64(iSeq);
        return true;
    }

    void ToNetByteOrder()
    {
        iLen = htonl(iLen);
        iCmd = htonl(iCmd);
        lUid = htonl64(lUid);
        iErr = htonl(iErr);
        // iSeq = htonl64(iSeq);
    }

    void ToHostByteOrder()
    {
        iLen = ntohl(iLen);
        iCmd = ntohl(iCmd);
        lUid = ntohl64(lUid);
        iErr = ntohl(iErr);
        // iSeq = ntohl64(iSeq);
    }
} MsgHead;

#pragma pack(pop)


#endif // __NET_MSG_H__