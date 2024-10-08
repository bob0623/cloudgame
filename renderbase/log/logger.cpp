#include "logger.h"
#include "logwriter.h"

#include <stdarg.h>
#include <errno.h>
#include <cstring>

#define TMP_BUF_SIZE 4096

namespace xlog
{

int init(const std::string& dir) {
    xlog::InitInfo info;
    info.log_mode = xlog::InitInfo::LOG_MODE_ASYNC;
    info.log_level = xlog::InitInfo::LOG_LEVEL_INFO;
    info.log_cache_limit = 1000;
    info.log_max_size_MB = 1;
    info.log_store_file_num = 5;
    info.log_dir = dir;
    info.also_log_to_stderr = true;
    return init(info);
}

int init(const xlog::InitInfo& ini)
{
	return XLogWriter::Instance()->init(ini);
}

int release()
{
	XLogWriter::Release();
	return xlog::RES_NO_ERROR;
}

int log(const char *format, ...)
{
    char buf[TMP_BUF_SIZE];
    memset(buf,0,sizeof(buf));
    char *p = buf;
    va_list args;
    va_start(args,format);
    int successCharacterNum = 0;
#if defined(LOG_OS_WIN)
    successCharacterNum = vsnprintf_s(p, _countof(buf), _TRUNCATE,format,args);
#else
    successCharacterNum = vsnprintf(p,TMP_BUF_SIZE-10,format,args);
#endif
    va_end(args);

    if ( successCharacterNum > 0 )
    {
        if ( successCharacterNum <= TMP_BUF_SIZE-10 )
            p += successCharacterNum;
        else
            p += TMP_BUF_SIZE-10;
    }
    else
    {
        memcpy(p, "logerror", 8);
        p += 8;
    }

    *p++ = '\r';
    *p++ = '\n';
    *p++ = '\0';

    std::string logStr;
    logStr.assign(buf, TMP_BUF_SIZE);
    return XLogWriter::Instance()->write_log(xlog::InitInfo::LOG_LEVEL_INFO, "INFO", logStr.c_str());
}

int logv(const char* format, ...)
{
    char buf[TMP_BUF_SIZE];
    memset(buf,0,sizeof(buf));
    char *p = buf;
    va_list args;
    va_start(args,format);
    int successCharacterNum = 0;
#if defined(LOG_OS_WIN)
    successCharacterNum = vsnprintf_s(p, _countof(buf), _TRUNCATE, format, args);
#else
    successCharacterNum = vsnprintf(p,TMP_BUF_SIZE-10,format,args);
#endif
    va_end(args);

    if ( successCharacterNum > 0 )
    {
        if ( successCharacterNum <= TMP_BUF_SIZE-10 )
            p += successCharacterNum;
        else
            p += TMP_BUF_SIZE-10;
    }
    else
    {
        memcpy(p, "logerror", 8);
        p += 8;
    }

    *p++ = '\r';
    *p++ = '\n';
    *p++ = '\0';

    std::string logStr;
    logStr.assign(buf, TMP_BUF_SIZE);
    return XLogWriter::Instance()->write_log(xlog::InitInfo::LOG_LEVEL_VERBOSE, "VERBOSE",logStr.c_str());
}

int logd(const char* format, ...)
{
    char buf[TMP_BUF_SIZE];
    memset(buf,0,sizeof(buf));
    char *p = buf;
    va_list args;
    va_start(args,format);
    int successCharacterNum = 0;
#if defined(LOG_OS_WIN)
    successCharacterNum = vsnprintf_s(p, _countof(buf), _TRUNCATE, format, args);
#else
    successCharacterNum = vsnprintf(p,TMP_BUF_SIZE-10,format,args);
#endif
    va_end(args);

    if ( successCharacterNum > 0 )
    {
        if ( successCharacterNum <= TMP_BUF_SIZE-10 )
            p += successCharacterNum;
        else
            p += TMP_BUF_SIZE-10;
    }
    else
    {
        memcpy(p, "logerror", 8);
        p += 8;
    }

    *p++ = '\r';
    *p++ = '\n';
    *p++ = '\0';

    std::string logStr;
    logStr.assign(buf, TMP_BUF_SIZE);
    return XLogWriter::Instance()->write_log(xlog::InitInfo::LOG_LEVEL_DEBUG, "DEBUG",logStr.c_str());
}
int logi(const char* format, ...)
{
    char buf[TMP_BUF_SIZE];
    memset(buf,0,sizeof(buf));
    char *p = buf;
    va_list args;
    va_start(args,format);
    int successCharacterNum = 0;
#if defined(LOG_OS_WIN)
    successCharacterNum = vsnprintf_s(p, _countof(buf), _TRUNCATE, format, args);
#else
    successCharacterNum = vsnprintf(p,TMP_BUF_SIZE-10,format,args);
#endif
    va_end(args);

    if ( successCharacterNum > 0 )
    {
        if ( successCharacterNum <= TMP_BUF_SIZE-10 )
            p += successCharacterNum;
        else
            p += TMP_BUF_SIZE-10;
    }
    else
    {
        memcpy(p, "logerror", 8);
        p += 8;
    }

    *p++ = '\r';
    *p++ = '\n';
    *p++ = '\0';

    std::string logStr;
    logStr.assign(buf, TMP_BUF_SIZE);
    return XLogWriter::Instance()->write_log(xlog::InitInfo::LOG_LEVEL_INFO, "INFO",logStr.c_str());
}

int logw(const char* format, ...)
{
    char buf[TMP_BUF_SIZE];
	memset(buf,0,sizeof(buf));
	char *p = buf;
	va_list args;
	va_start(args,format);
    int successCharacterNum = 0;
#if defined(LOG_OS_WIN)
    successCharacterNum = vsnprintf_s(p, _countof(buf), _TRUNCATE, format, args);
#else
    successCharacterNum = vsnprintf(p,TMP_BUF_SIZE-10,format,args);
#endif
	va_end(args);

    if ( successCharacterNum > 0 )
    {
        if ( successCharacterNum <= TMP_BUF_SIZE-10 )
            p += successCharacterNum;
        else
            p += TMP_BUF_SIZE-10;
    }
    else
    {
        memcpy(p, "logerror", 8);
        p += 8;
    }

	*p++ = '\r';
	*p++ = '\n';
	*p++ = '\0';

	std::string logStr;
    logStr.assign(buf, TMP_BUF_SIZE);
	return XLogWriter::Instance()->write_log(xlog::InitInfo::LOG_LEVEL_WARN, "‼️ WARN",logStr.c_str());
}

int loge(const char* format, ...)
{
    char buf[TMP_BUF_SIZE];
	memset(buf,0,sizeof(buf));
	char *p = buf;
	va_list args;
	va_start(args,format);
    int successCharacterNum = 0;
#if defined(LOG_OS_WIN)
    successCharacterNum = vsnprintf_s(p, _countof(buf), _TRUNCATE, format, args);
#else
    successCharacterNum = vsnprintf(p,TMP_BUF_SIZE-10,format,args);
#endif
	va_end(args);

    if ( successCharacterNum > 0 )
    {
        if ( successCharacterNum <= TMP_BUF_SIZE-10 )
            p += successCharacterNum;
        else
            p += TMP_BUF_SIZE-10;
    }
    else
    {
        memcpy(p, "logerror", 8);
        p += 8;
    }

	*p++ = '\r';
	*p++ = '\n';
	*p++ = '\0';

	std::string logStr;
    logStr.assign(buf, TMP_BUF_SIZE);
	return XLogWriter::Instance()->write_log(xlog::InitInfo::LOG_LEVEL_ERROR, "❌ ERROR",logStr.c_str());
}

}
