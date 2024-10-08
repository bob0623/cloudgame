#include "commonutils.h"
#include <bit>
#include <iostream>
#include <boost/asio.hpp>

uint32_t CommonUtils::ipToInt(std::string ip)
{
	return boost::asio::ip::make_address_v4(ip).to_uint();
}

std::string CommonUtils::intToIP(uint32_t ip)
{
	return boost::asio::ip::make_address_v4(ip).to_string();
}

uint64_t CommonUtils::mergeIPAndPort(uint32_t ip, uint32_t port)
{
	uint32_t key = 0;
#if __cplusplus >= 202002L //C++ 20 support std::bit_cast;
	key = std::bit_cast<uint64_t>(ip) << 32 | std::bit_cast<uint64_t>(port);
#else
	key = ((uint64_t)ip << 32) | port;
#endif
	return key;
}

uint32_t CommonUtils::castIPAndPort(uint64_t key, uint32_t& ip, uint32_t& port)
{
#if __cplusplus >= 202002L //C++ 20 support std::bit_cast;
	ip = std::bit_cast<int>(key >> 32);
	port = std::bit_cast<int>(key & 0xFFFFFFFF);
#else
	ip = (key >> 32) & 0xFFFFFFFF;
	port = key & 0xFFFFFFFF;
#endif
	return ip;
}