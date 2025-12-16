#ifndef _THIRD_LOG_H__
#define _THIRD_LOG_H__

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>

using namespace std;

//
extern void trace(const char *filename, const char *func, const int32_t line, const int32_t level, const char *format,  ...);

//
#define THIRD_DEBUG(format, args...) trace(__FILE__, __FUNCTION__,  __LINE__, 0, format, ##args)
#define THIRD_INFO(format,  args...) trace(__FILE__, __FUNCTION__,  __LINE__, 1, format, ##args)
#define THIRD_WARN(format,  args...) trace(__FILE__, __FUNCTION__,  __LINE__, 2, format, ##args)
#define THIRD_ERROR(format, args...) trace(__FILE__, __FUNCTION__,  __LINE__, 3, format, ##args)

#endif

