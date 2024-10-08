#pragma once

#ifdef _WIN32
#define RENDERBASE_API	__declspec( dllexport )
#define UNUSED (void)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <combaseapi.h>
#include <winsock2.h>
#include <process.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef WIN32
#include "util/byteswap.h"
#endif

#include "int_types.h"
