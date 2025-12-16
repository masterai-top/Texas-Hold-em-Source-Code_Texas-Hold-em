#include "ThirdLog.h"
#include "LogComm.h"
#include "servant/Application.h"
#include "OuterFactoryImp.h"

using namespace std;
using namespace tars;

/**
 * 日志输出函数
 */
void trace(const char *filename, const char *func, const int32_t line, const int32_t level, const char *format,  ...)
{
    timespec timeSpec;
    clock_gettime(CLOCK_REALTIME, &timeSpec);

    tm nowTime;
    localtime_r(&timeSpec.tv_sec, &nowTime);
    static char current[128];
    sprintf(current, "%04d-%02d-%02d %02d:%02d:%02d",
            nowTime.tm_year + 1900,
            nowTime.tm_mon + 1,
            nowTime.tm_mday,
            nowTime.tm_hour,
            nowTime.tm_min,
            nowTime.tm_sec);

    char buf[4096] = {0};
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf) - 1, format, args);
    va_end(args);

    if (level == 0)
    {
        // LOG_DEBUG << "[" << filename << ":" << line << ":" << func << "]" << buf << endl;
        LOG->debug() << "[" << filename << ":" << line << ":" << func << "] " << pthread_self() << " " << buf << endl;
    }
    else if (level == 1)
    {
        // LOG_INFO << "[" << filename << ":" << line << ":" << func << "]" << buf << endl;
        LOG->info() << "[" << filename << ":" << line << ":" << func << "] " << pthread_self() << " " << buf << endl;
    }
    else if (level == 2)
    {
        // LOG_WARN << "[" << filename << ":" << line << ":" << func << "]" << buf << endl;
        LOG->warn() << "[" << filename << ":" << line << ":" << func << "] " << pthread_self() << " " << buf << endl;
    }
    else if (level == 3)
    {
        // LOG_ERROR << "[" << filename << ":" << line << ":" << func << "]" << buf << endl;
        LOG->error() << "[" << filename << ":" << line << ":" << func << "] " << pthread_self() << " " << buf << endl;
    }
    else
    {
        // LOG_DEBUG << "[" << filename << ":" << line << ":" << func << "]" << buf << endl;
        LOG->debug() << "[" << filename << ":" << line << ":" << func << "] " << pthread_self() << " " << buf << endl;
    }
}
