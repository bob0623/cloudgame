#include "tcpdatahandler.h"
#include <iostream>   
#include <vector>  
#include "../proto/inputcmd.pb.h"

using namespace boost::interprocess;
const std::string MQName = "rendercmdmq";
const int MaxMsgNumber = 100;
const int MaxMsgSize = 1024;

TCPDataHandler::TCPDataHandler()
{
	message_queue::remove(MQName.c_str());
	m_mq = new message_queue(open_or_create, MQName.c_str(), MaxMsgNumber, MaxMsgSize);
}

TCPDataHandler::~TCPDataHandler()
{
    message_queue::remove(MQName.c_str());
    delete m_mq;
    m_mq = NULL;
}

void TCPDataHandler::handleData(const char* data, int length)
{
    try {
        //std::string buf = serialize(data, length);
        //m_mq->send(buf.c_str(), buf.length(), 0);
        //m_mq->send(data, length, 0);

        bool ret = m_mq->try_send(data, length, 0);
        if (!ret) {
            std::cout << "failed to send data to mq, maybe mq is full." << std::endl;
        }
        render::CMDMessage msg;
        msg.ParseFromString(data);
        std::cout << "recv content: " << msg.content() << std::endl;
    }
    catch (interprocess_exception& ex) {
        std::cout << "TCPDataHandler::handleData: " << ex.what() << std::endl;
    }
}

std::string TCPDataHandler::serialize(const char* str, int length)
{
    std::ostringstream oss;
    oss.write(reinterpret_cast<const char*>(&length), sizeof(length));
    oss << str;
    return oss.str();
}

void TCPDataHandler::deserialize(std::string& serialized, int& length, std::string& str) 
{
    std::istringstream iss(serialized);
    iss.read(reinterpret_cast<char*>(&length), sizeof(length));
    str.resize(length);
    iss.read(&str[0], length);
    serialized = serialized.substr(sizeof(length) + length);
}
