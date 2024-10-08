#pragma once

#include "logger.h"

#include <mutex>
#include <string>
#include <vector>

#if defined(LOG_OS_WIN)
#include <Windows.h>
#else
#include <pthread.h>
#endif

class XMutex;
class LogQueue;
class XLogWriter
{
public:
	static XLogWriter* Instance();
	static void Release();

public:
	int init(const xlog::InitInfo& ini);
	int write_log(xlog::InitInfo::LOG_LEVEL logLevel, const std::string& levelstr, const std::string& log);

	void run(); //Async mode, thread

private:
	XLogWriter();
	~XLogWriter();

	int create_log_file();
    int delete_expire_log_files();
	int start(); //Async mode, thread
	int stop(); //Async mode, thread
	void sleep(int millsecs);
	std::string timestampstr();

private:
	static XLogWriter*	m_pIns;
	xlog::InitInfo	m_ini;
	FILE*		m_pLogFile;
	size_t		m_iLogSize;
    LogQueue*   m_pQueue;
    std::mutex* m_pMutex;
	volatile bool m_bStopped;

#if defined(LOG_OS_WIN)
	HANDLE		m_hThread;
#else
	pthread_t	m_hThread;
#endif
};
