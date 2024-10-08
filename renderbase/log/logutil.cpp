#include "logutil.h"

static int32_t k_xutil_pid = 0;

#ifdef _WIN32
static int gettimeofday(struct timeval *tv, void* tz)
{
	(void)tz;
#define EPOCHFILETIME (116444736000000000ULL)
	FILETIME ft;
	LARGE_INTEGER li;
	uint64_t tt;

	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	tt = (li.QuadPart - EPOCHFILETIME) / 10;
	tv->tv_sec = (long)(tt / 1000000);
	tv->tv_usec = tt % 1000000;

	return 0;
}
#endif

void xutil_systime(long& o_sec, long& o_usec)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	o_sec = tv.tv_sec;
	o_usec = tv.tv_usec;
}

int64_t xutil_systime64()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return static_cast<int64_t>(tv.tv_sec) * 1000 + tv.tv_usec / 1000;
}

int32_t xutil_getpid()
{
	if ( 0 == k_xutil_pid )
		k_xutil_pid = _getpid();
	return k_xutil_pid;
}

std::string xutil_gethostname()
{
	std::string hostnamestr = "unknown";
#ifdef _WIN32
	char buf[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD len = MAX_COMPUTERNAME_LENGTH + 1;
	if ( GetComputerNameA(buf,&len) )
	{
		hostnamestr = buf;
	}
	else
	{
		hostnamestr.clear();
	}
#else
    struct utsname buf;
    if(0 != uname(&buf)) {
        // ensure null termination on failure
        *buf.nodename = '\0';
    }
    hostnamestr = buf.nodename;
#endif
	return hostnamestr;
}
