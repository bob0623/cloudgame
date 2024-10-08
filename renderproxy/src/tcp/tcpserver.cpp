#include "tcpserver.h"
#include "renderbase/log/logger.h"
#include "util/commonutils.h"

#include<iostream>

TCPServer::TCPServer(boost::asio::io_context& ioc, int port) 
	:m_ioc(ioc), 
	m_acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
	startNewSession();
}

TCPServer::~TCPServer()
{
	for (std::map<uint64_t, TCPSession*>::iterator it = m_sessions.begin(); it != m_sessions.end(); it++) {
		delete it->second;
		it->second = NULL;
	}
	m_sessions.clear();
}

void TCPServer::startNewSession()
{
	try
	{
		TCPSession* session = new TCPSession(m_ioc);
		m_acceptor.async_accept(session->getSocket(), std::bind(&TCPServer::acceptHandle, this, session, std::placeholders::_1));
	}
	catch (boost::system::system_error& e)
	{
		FUNLOGE("system error occured: %s", e.what());
		std::cout << e.what() << std::endl;
	}
}

void TCPServer::acceptHandle(TCPSession* session, const boost::system::error_code& error)
{
	if (!error)
	{
		uint32_t ip = CommonUtils::getInstance()->ipToInt(session->getSocket().remote_endpoint().address().to_string());
		uint32_t port = session->getSocket().remote_endpoint().port();
		FUNLOG("accept a socket, ip=%s, port=%d", session->getSocket().remote_endpoint().address(), session->getSocket().remote_endpoint().port());
		std::cout << "accept a socket, ip: " << session->getSocket().remote_endpoint().address() << ", port:" << session->getSocket().remote_endpoint().port()<<", merged key: "<< CommonUtils::getInstance()->mergeIPAndPort(ip, port)<<", session: "<< session << std::endl;
		m_sessions[CommonUtils::getInstance()->mergeIPAndPort(ip, port)] = session;
		session->start();
	}
	else
	{
		std::cout << "TCPServer::acceptHandle error:" << error.message()<<std::endl;
		delete session;
	}
	startNewSession();
}