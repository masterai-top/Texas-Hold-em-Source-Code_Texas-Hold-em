#include "RawBuffer.h"
#include "ThirdLog.h"

#define CACHE_MAXLEN (65536)

CRawBuffer::CRawBuffer()
{
    _bufLen = 8 * 1024;
    _headPos = 0;
    _tailPos = 0;
    _buffer = (char *)malloc(_bufLen);
}

CRawBuffer::~CRawBuffer()
{
    if (_buffer)
    {
        free(_buffer);
        _buffer = NULL;
    }
}

//
char *CRawBuffer::data() const
{
    if (!_buffer)
    {
        THIRD_ERROR("_buffer is null");
        return NULL;
    }

    if ((_headPos < 0) || (_headPos > _bufLen))
    {
        THIRD_ERROR("_headPos invalid, HeadPos[%d], BufLen[%d]", _headPos, _bufLen);
        return NULL;
    }

    if ((_tailPos < 0) || (_tailPos > _bufLen))
    {
        THIRD_ERROR("_tailPos invalid, TailPos[%d], BufLen[%d]", _tailPos, _bufLen);
        return NULL;
    }

    if (_tailPos < _headPos)
    {
        THIRD_ERROR("_tailPos or _headPos invalid, TailPos[%d], HeadPos[%d]", _tailPos, _headPos);
        return NULL;
    }

    return &(_buffer[_headPos]);
}

//
char *CRawBuffer::data(const int32_t &offset) const
{
    if (!_buffer)
    {
        THIRD_ERROR("_buffer is null");
        return NULL;
    }

    if (_headPos < 0 || _headPos > _bufLen)
    {
        THIRD_ERROR("_headPos invalid, HeadPos[%d], BufLen[%d]", _headPos, _bufLen);
        return NULL;
    }

    if (_tailPos < 0 || _tailPos > _bufLen)
    {
        THIRD_ERROR("_tailPos invalid, TailPos[%d], BufLen[%d]", _tailPos, _bufLen);
        return NULL;
    }

    if (_tailPos < (_headPos + offset))
    {
        THIRD_ERROR("_tailPos or _headPos invalid, TailPos[%d], HeadPos[%d], Offset[%d]", _tailPos, _headPos, offset);
        return NULL;
    }

    return &(_buffer[_headPos + offset]);
}

//
int32_t CRawBuffer::size() const
{
    if (!_buffer)
    {
        THIRD_ERROR("_buffer is null");
        return -1;
    }

    if (_headPos < 0 || _headPos > _bufLen)
    {
        THIRD_ERROR("_headPos invalid, HeadPos[%d], BufLen[%d]", _headPos, _bufLen);
        return -1;
    }

    if (_tailPos < 0 || _tailPos > _bufLen)
    {
        THIRD_ERROR("_tailPos invalid, TailPos[%d], BufLen[%d]", _tailPos, _bufLen);
        return -1;
    }

    if (_tailPos < _headPos)
    {
        THIRD_ERROR("_tailPos or _headPos invalid, TailPos[%d], HeadPos[%d]", _tailPos, _headPos);
        return -1;
    }

    return (_tailPos - _headPos);
}

//
const int32_t CRawBuffer::capacity()
{
    return _bufLen;
}

//
const int32_t CRawBuffer::available()
{
    if (-1 == size())
        return -1;

    return _bufLen - size();
}

//
int32_t CRawBuffer::append(const char *ptr, const int32_t &len)
{
    Lock sync(*this);

    if (!_buffer)
    {
        THIRD_ERROR("_buffer is null");
        return -1;
    }

    if (len < 0)
    {
        THIRD_ERROR("invalid len, len[%d]", len);
        return -1;
    }

    if (len == 0)
    {
        THIRD_DEBUG("len is zero");
        return 0;
    }

    int32_t nData = _tailPos - _headPos;
    int32_t nSpace = _bufLen - _tailPos;
    if (nData < 0 || nSpace < 0)
    {
        THIRD_ERROR("Tnternal error: nData[%d], nSpace[%d], nHead[%d], nTail[%d], nBufSize[%d]", nData, nSpace, _headPos, _tailPos, _bufLen);
        return -1;
    }

    if (nSpace < len)
    {
        memmove(&(_buffer[0]), &(_buffer[_headPos]), nData);
        _headPos = 0;
        _tailPos = nData;
        // THIRD_DEBUG("Cache memmove<1>: nData[%d], nAppend[%d], nHead[%d], nTail[%d], nBufSize[%d]", nData, len, _headPos, _tailPos, _bufLen);
    }

    nSpace = _bufLen - _tailPos;
    // THIRD_DEBUG("Tail space: nData[%d], nSpace[%d], nHead[%d], nTail[%d], nBufSize[%d]", nData, nSpace, _headPos, _tailPos, _bufLen);
    if (nSpace < len)
    {
        const int32_t nNewSize = _bufLen * 2;
        if (nNewSize > CACHE_MAXLEN)
        {
            THIRD_ERROR("Not enough memory(1): nBufSize[%d], nAppend[%d], nHead[%d], nTail[%d]", _bufLen, len, _headPos, _tailPos);
            THIRD_ERROR("Not enough memory(2): nNewSize[%d], nData[%d], nSpaceSize[%d]", nNewSize, nData, nSpace);
            return -1;
        }

        // char *pNewBuf = (char *)realloc(_buffer, nNewSize);
        // if (!pNewBuf)
        // {
        //     THIRD_ERROR("Out of memory, nNewSize[%d]", nNewSize);
        //     return -1;
        // }
        //
        char *pNewBuf = (char *)malloc(nNewSize);
        if (!pNewBuf)
        {
            THIRD_ERROR("Out of memory(1), nNewSize[%d]", nNewSize);
            return -1;
        }

        int32_t iLen = _tailPos - _headPos;
        if (iLen < 0 || iLen > CACHE_MAXLEN)
        {
            THIRD_ERROR("Out of memory(2), iLen[%d]", iLen);
            return -1;
        }

        memcpy(pNewBuf, &_buffer[_headPos], iLen);

        if (_buffer)
        {
            free(_buffer);
            _buffer = NULL;
        }
        else
        {
            THIRD_ERROR("Out of memory(3), iLen[%d]", iLen);
            return -1;
        }

        _buffer = pNewBuf;
        _bufLen = nNewSize;
        _headPos = 0;
        _tailPos = iLen;

        // THIRD_DEBUG("Cache capacity<1>: nBufSize[%d], nAppend[%d], nHead[%d], nTail[%d]", _bufLen, len, _headPos, _tailPos);
        // THIRD_DEBUG("Cache capacity<2>: nNewSize[%d], nData[%d], _bufLen[%d]", nNewSize, nData, _bufLen);
    }

    memcpy(&(_buffer[_tailPos]), ptr, len);
    _tailPos += len;
    // THIRD_DEBUG("Append data succ, ptr[%p], len[%d], head[%d], tail[%d], available[%d]", ptr, len, _headPos, _tailPos, _bufLen);
    return 0;
}

//
int32_t CRawBuffer::recycle(const int32_t &len)
{
    Lock sync(*this);

    if (len < 0)
    {
        THIRD_ERROR("invalid len, len[%d]", len);
        return -1;
    }

    if (len > (_tailPos - _headPos))
    {
        THIRD_ERROR("Parameter error, len[%d], cur[%d]", len, _tailPos - _headPos);
        return 0;
    }

    _headPos += len;
    // THIRD_DEBUG("recycle data: len[%d], remain[%d], head[%d], tail[%d]", len, _tailPos - _headPos, _headPos, _tailPos);
    return 0;
}

//
void CRawBuffer::reset()
{
    Lock sync(*this);
    _headPos = 0;
    _tailPos = 0;
}
