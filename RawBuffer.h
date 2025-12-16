#ifndef _RAW_BUFFER_H__
#define _RAW_BUFFER_H__

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "util/tc_thread.h"
#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace tars;


class CRawBuffer : public TC_ThreadLock
{
public:
    CRawBuffer();
    virtual ~CRawBuffer();

    /**
     * 获取缓存指针
     */
    char *data() const;

    /**
    * 获取缓存指针
    */
    char *data(const int32_t &offset) const;

    /**
     * 获取缓存长度
     */
    int32_t size() const;

    /**
     * 获取缓存容量
     */
    const int32_t capacity();

    /**
     * 获取有效空间
     */
    const int32_t available();

    /**
     * 缓存追加数据
     */
    int32_t append(const char *ptr, const int32_t &len);

    /**
     * 释放缓存数据
     */
    int32_t recycle(const int32_t &len);

    /**
     * 重置数据缓存
     */
    void reset();

private:
    /**
     * 缓存指针
     */
    char *_buffer;
    /**
     * 缓存区大小
     */
    volatile int32_t _bufLen;
    /**
     * 数据头部位置
     */
    volatile int32_t _headPos;
    /**
     * 数据尾部位置
     */
    volatile int32_t _tailPos;
};

#endif

