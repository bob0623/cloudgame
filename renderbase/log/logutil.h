#pragma once

#include "common/config.h"

#include <string>

void xutil_systime(long& o_sec, long& o_usec);
int64_t xutil_systime64();
int32_t xutil_getpid();
std::string xutil_gethostname();
