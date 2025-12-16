#ifndef  __THIRDPARTY_MANAGER_H__
#define  __THIRDPARTY_MANAGER_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "OuterFactoryImp.h"
#include "servant/Application.h"
#include "servant/Communicator.h"
#include "LogComm.h"
#include "TcpClient.h"
#include "ThirdLog.h"
#include "NetMsg.h"
#include "util/tc_thread.h"
#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace tars;

/**
 * 第三方管理类
 */
class CThirdPartyManager
{
public:
    CThirdPartyManager();
    virtual ~CThirdPartyManager();

    //
    bool init();
    //
    bool loop();
    //
    bool final();
    //
    bool check();
    //
    void testing();

public:
    //
    CTcpClient *getAiProxy(const uint32_t &tableId);

private:
    //
    CAsyncEpoller *_asyncEpoller;
    //
    CTcpClient *_tcpClient;
    //
    std::map<uint32_t, CTcpClient *> _mapTables;
};

#endif

