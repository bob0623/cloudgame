#pragma once
#include "proto/inputcmd.pb.h"
#include <boost/interprocess/ipc/message_queue.hpp>   

class TCPDataHandler
{
public:
	TCPDataHandler();
	~TCPDataHandler();

	void handleData(const char* data, int length);
private:
	std::string serialize(const char* str, int num);
	void deserialize(std::string& serialized, int& num, std::string& str);

private:
	boost::interprocess::message_queue* m_mq;
};

