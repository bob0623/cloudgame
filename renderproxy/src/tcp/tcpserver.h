#pragma once
#include<boost/asio.hpp>
#include"tcpsession.h"
#include <map>

class TCPServer
{
public:
	TCPServer(boost::asio::io_context& ioc, int port);
	~TCPServer();

private:
	void acceptHandle(TCPSession* session, const boost::system::error_code& error);
	void startNewSession();

private:
	boost::asio::io_context& m_ioc;
	boost::asio::ip::tcp::acceptor m_acceptor;
	std::map<uint64_t, TCPSession*> m_sessions;
};
