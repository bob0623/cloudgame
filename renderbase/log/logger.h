#pragma once
#include <string>
#define LOG_OS_ANDROID
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
    #define LOG_OS_WIN
#elif defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
    #define LOG_OS_APPLE

#elif defined(__ANDROID__)
    #define LOG_OS_ANDROID
#endif

#if defined(LOG_OS_WIN)
#define LOGSDK2_API __declspec( dllexport )

#define FUNLOG(fmt, ...)	xlog::log("[%s]: " fmt, __FUNCTION__, __VA_ARGS__)
#define FUNLOGV(fmt, ...)   xlog::logv("[%s]: " fmt, __FUNCTION__, __VA_ARGS__)
#define FUNLOGD(fmt, ...)   xlog::logd("[%s]: " fmt, __FUNCTION__, __VA_ARGS__)
#define FUNLOGI(fmt, ...)	xlog::logi("[%s]: " fmt, __FUNCTION__, __VA_ARGS__)
#define FUNLOGW(fmt, ...)	xlog::logw("[%s]: " fmt, __FUNCTION__, __VA_ARGS__)
#define FUNLOGE(fmt, ...)	xlog::loge("[%s]: " fmt, __FUNCTION__, __VA_ARGS__)
#elif defined(LOG_OS_APPLE)
#define LOGSDK2_API

#define __CLASS_NAME__ (typeid(*this).name())
#define FUNLOG(fmt, ...)    xlog::log("[%s::%s]: " fmt, __CLASS_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGV(fmt, ...)   xlog::logv("[%s::%s]: " fmt, __CLASS_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGD(fmt, ...)   xlog::logd("[%s::%s]: " fmt, __CLASS_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGI(fmt, ...)	xlog::logi("[%s::%s]: " fmt, __CLASS_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGW(fmt, ...)	xlog::logw("[%s::%s]: " fmt, __CLASS_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGE(fmt, ...)	xlog::loge("[%s::%s]: " fmt, __CLASS_NAME__, __FUNCTION__, ##__VA_ARGS__)

#define __CLASS_OBJC_NAME__ (typeid(*self).name())
#define FUNLOG_OBJC(fmt, ...)    LOG("[%s::%s]: " fmt, __CLASS_OBJC_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGV_OBJC(fmt, ...)   LOGV("[%s:%s]: " fmt, __CLASS_OBJC_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGD_OBJC(fmt, ...)   LOGD("[%s:%s]: " fmt, __CLASS_OBJC_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGI_OBJC(fmt, ...)   LOGI("[%s:%s]: " fmt, __CLASS_OBJC_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGW_OBJC(fmt, ...)   LOGW("[%s:%s]: " fmt, __CLASS_OBJC_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGE_OBJC(fmt, ...)   LOGE("[%s:%s]: " fmt, __CLASS_OBJC_NAME__, __FUNCTION__, ##__VA_ARGS__)

#elif defined(LOG_OS_ANDROID)
#define LOGSDK2_API

#include <typeinfo>
#define __CLASS_NAME__ (typeid(*this).name())

#define FUNLOG(fmt, ...)	xlog::log(" [%s:%s]: " fmt, __CLASS_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGV(fmt, ...)   xlog::logv("[%s:%s]: " fmt, __CLASS_NAME__,  __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGD(fmt, ...)   xlog::logd("[%s:%s]: " fmt, __CLASS_NAME__,  __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGI(fmt, ...)	xlog::logi("[%s:%s]: " fmt, __CLASS_NAME__,  __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGW(fmt, ...)	xlog::logw("[%s:%s]: " fmt, __CLASS_NAME__, __FUNCTION__, ##__VA_ARGS__)
#define FUNLOGE(fmt, ...)	xlog::loge("[%s:%s]: " fmt, __CLASS_NAME__,  __FUNCTION__, ##__VA_ARGS__)

#endif

#define LOG		xlog::log
#define LOGV    xlog::logv
#define LOGD    xlog::logd
#define LOGI	xlog::logi
#define LOGW	xlog::logw
#define LOGE	xlog::loge

namespace xlog
{
struct InitInfo
{
	enum LOG_MODE {LOG_MODE_SYNC = 0, LOG_MODE_ASYNC = 1};
    enum LOG_LEVEL
    {
        LOG_LEVEL_NONE    = 0,
        LOG_LEVEL_ERROR   = 1,
        LOG_LEVEL_WARN    = 2,
        LOG_LEVEL_INFO    = 3,
        LOG_LEVEL_DEBUG   = 4,
        LOG_LEVEL_VERBOSE = 5,
        LOG_LEVEL_ALL     = 100,
    };
	LOG_MODE	log_mode;
    LOG_LEVEL   log_level;
	int			log_cache_limit; //Async mode, cache upper limit
	int			log_max_size_MB; //max size(MB) for a single log file
    int         log_store_file_num; //how many log files can be stored
	std::string log_dir;
	bool		also_log_to_stderr; //also log to console

    InitInfo(): log_mode(LOG_MODE_SYNC), log_level(LOG_LEVEL_INFO), log_cache_limit(100), log_max_size_MB(100), log_store_file_num(10), also_log_to_stderr(true) {}
};

enum
{
	RES_NO_ERROR = 0,
	RES_ERROR_OPEN_LOG_FAIL = -1000,
	RES_ERROR_NO_LOGFILE,
	RES_START_THREAD_FAIL
};

LOGSDK2_API int init(const std::string& dir);
LOGSDK2_API int init(const InitInfo& ini);
LOGSDK2_API int release();
LOGSDK2_API int log(const char *format, ...);
LOGSDK2_API int logv(const char* format, ...);
LOGSDK2_API int logd(const char* format, ...);
LOGSDK2_API int logi(const char* format, ...);
LOGSDK2_API int logw(const char* format, ...);
LOGSDK2_API int loge(const char* format, ...);
}
