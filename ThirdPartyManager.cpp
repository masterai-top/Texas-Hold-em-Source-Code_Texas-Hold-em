#include "ThirdPartyManager.h"
#include "AIServer.h"


CThirdPartyManager::CThirdPartyManager(): _asyncEpoller(NULL), _tcpClient(NULL)
{

}

CThirdPartyManager::~CThirdPartyManager()
{
    if (_tcpClient)
    {
        delete _tcpClient;
        _tcpClient = NULL;
    }

    if (_asyncEpoller)
    {
        delete _asyncEpoller;
        _asyncEpoller = NULL;
    }
}

bool CThirdPartyManager::init()
{
    if (_asyncEpoller)
    {
        _asyncEpoller->final();
        delete _asyncEpoller;
        _asyncEpoller = NULL;
    }

    _asyncEpoller = new CAsyncEpoller();
    if (!_asyncEpoller)
    {
        LOG_ERROR << "_asyncEpoller is null." << endl;
        return false;
    }

    return _asyncEpoller->init(1000);
}

bool CThirdPartyManager::loop()
{
    if (!_asyncEpoller)
    {
        LOG_ERROR << "_asyncEpoller is null." << endl;
        return false;
    }

    return _asyncEpoller->loop();
}

bool CThirdPartyManager::final()
{
    if (!_asyncEpoller)
    {
        LOG_ERROR << "_asyncEpoller is null." << endl;
        return false;
    }

    return _asyncEpoller->final();
}

bool CThirdPartyManager::check()
{
    if (!_tcpClient)
    {
        return false;
    }

    _tcpClient->connectChecker();
    return true;
}

void CThirdPartyManager::testing()
{
    // _tcpClient = new CTcpClient(_asyncEpoller);
    // if (!_tcpClient)
    // {
    //     LOG_ERROR << "_tcpClient is null" << endl;
    //     return;
    // }

    // _tcpClient->setSvrAddr(g_app.getOuterFactoryPtr()->getAiPlatformAddr().c_str());
    // _tcpClient->setSvrPort(g_app.getOuterFactoryPtr()->getAiPlatformPort());
    // if (-1 == _tcpClient->Connect())
    // {
    //     THIRD_ERROR("Connection to server failed, err=%s", strerror(errno));
    //     return;
    // }

    // THIRD_DEBUG("Connection to server succeed, err=%s", strerror(errno));
    return;
}

CTcpClient *CThirdPartyManager::getAiProxy(const uint32_t &tableId)
{
    if (_tcpClient)
    {
        _tcpClient->connectChecker();
    }

    // THIRD_DEBUG("Get the proxy object, tableId:%u", tableId);
    return _tcpClient;
}

