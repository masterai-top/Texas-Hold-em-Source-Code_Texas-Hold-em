#include "NetMsg.h"

uint64_t htonl64(uint64_t host64)
{
    uint64_t ret = 0;
    uint32_t high = 0;
    uint32_t low = 0;
    low  = host64 & 0xFFFFFFFF;
    high = (host64 >> 32) & 0xFFFFFFFF;
    low  = htonl(low);
    high = htonl(high);
    ret  = low;
    ret  <<= 32;
    ret  |=  high;
    return ret;
}

uint64_t ntohl64(uint64_t net64)
{
    uint64_t ret = 0;
    uint32_t high = 0;
    uint32_t low = 0;
    low  = net64 & 0xFFFFFFFF;
    high = (net64 >> 32) & 0xFFFFFFFF;
    low  = ntohl(low);
    high = ntohl(high);
    ret  = low;
    ret  <<= 32;
    ret  |=  high;
    return ret;
}
