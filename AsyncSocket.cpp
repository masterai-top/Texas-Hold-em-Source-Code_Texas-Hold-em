#include "AsyncSocket.h"
#include "ThirdLog.h"

CAsyncSocket::CAsyncSocket(CAsyncEpoller *epoller) : _epoller(epoller)
{
    _fd = -1;
    _connected = false;
    _lastAccessTime = 0;
    memset(&_ev, 0x00, sizeof(_ev));
}

CAsyncSocket::~CAsyncSocket()
{
    _lastAccessTime = 0;
}

bool CAsyncSocket::disableInput()
{
    if (-1 == _fd)
    {
        THIRD_ERROR("Invalid socket");
        return false;
    }

    memset(&_ev, 0, sizeof(_ev));
    _ev.data.fd = _fd;
    _ev.data.ptr = this;
    _ev.events = EPOLLET | EPOLLOUT | EPOLLERR;
    if (-1 == epoll_ctl(epoller()->getEpfd(), EPOLL_CTL_MOD, _fd, &_ev))
    {
        THIRD_ERROR("Disable input: fd=%d, error=%s", _fd, strerror(errno));
        return false;
    }

    return true;
}

bool CAsyncSocket::enableInput()
{
    if (-1 == _fd)
    {
        THIRD_ERROR("Invalid socket");
        return false;
    }

    memset(&_ev, 0, sizeof(_ev));
    _ev.data.fd = _fd;
    _ev.data.ptr = this;
    _ev.events = EPOLLET | EPOLLIN | EPOLLOUT | EPOLLERR;
    if (-1 == epoll_ctl(epoller()->getEpfd(), EPOLL_CTL_MOD, _fd, &_ev))
    {
        THIRD_ERROR("Enable input: fd=%d, error=%s", _fd, strerror(errno));
        return false;
    }

    return true;
}

bool CAsyncSocket::disableOutput()
{
    if (-1 == _fd)
    {
        THIRD_ERROR("Invalid socket");
        return false;
    }

    memset(&_ev, 0, sizeof(_ev));
    _ev.data.fd = _fd;
    _ev.data.ptr = this;
    _ev.events = EPOLLET | EPOLLIN | EPOLLERR;
    if (-1 == epoll_ctl(epoller()->getEpfd(), EPOLL_CTL_MOD, _fd, &_ev))
    {
        THIRD_ERROR("Disable output: fd=%d, error=%s", _fd, strerror(errno));
        return false;
    }

    return true;
}

bool CAsyncSocket::enableOutput()
{
    if (-1 == _fd)
    {
        THIRD_ERROR("Invalid socket");
        return false;
    }

    memset(&_ev, 0, sizeof(_ev));
    _ev.data.fd = _fd;
    _ev.data.ptr = this;
    _ev.events = EPOLLET | EPOLLIN | EPOLLOUT | EPOLLERR;
    if (-1 == epoll_ctl(epoller()->getEpfd(), EPOLL_CTL_MOD, _fd, &_ev))
    {
        THIRD_ERROR("Enable output: fd=%d, error=%s", _fd, strerror(errno));
        return false;
    }

    return true;
}

bool CAsyncSocket::addEpoller()
{
    memset(&_ev, 0, sizeof(_ev));
    _ev.data.fd = getFd();
    _ev.data.ptr = this;
    _ev.events = EPOLLET | EPOLLIN | EPOLLERR;
    return epoller()->addEpoller(this);
}

bool CAsyncSocket::delEpoller()
{
    memset(&_ev, 0, sizeof(_ev));
    _ev.data.fd = getFd();
    _ev.data.ptr = this;
    _ev.events = EPOLLET | EPOLLIN | EPOLLOUT | EPOLLERR;
    return epoller()->delEpoller(this);
}

int32_t CAsyncSocket::getFd()
{
    return _fd;
}

void CAsyncSocket::setFd(int32_t fd)
{
    _fd = fd;
}

struct epoll_event *CAsyncSocket::getEvents()
{
    return &_ev;
}

CAsyncEpoller *CAsyncSocket::epoller()
{
    return _epoller;
}

uint64_t CAsyncSocket::getLastAccessTime()
{
    return _lastAccessTime;
}

void CAsyncSocket::setLastAccessTime(uint64_t ts)
{
    _lastAccessTime = ts;
}

bool CAsyncSocket::isConnected()
{
    return _connected;
}

void CAsyncSocket::setConnected(bool flags)
{
    _connected = flags;
}
