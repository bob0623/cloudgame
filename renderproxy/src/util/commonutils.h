#pragma once

#include "renderbase/util/singleton.h"

#include <string>
class CommonUtils
{
public:
	uint32_t ipToInt(std::string ip);
	std::string intToIP(uint32_t ip);

	uint64_t mergeIPAndPort(uint32_t ip, uint32_t port);
	uint32_t castIPAndPort(uint64_t key, uint32_t& ip, uint32_t& port);

private:
	SINGLETON(CommonUtils);
	CommonUtils() {};
	~CommonUtils() {};
};

