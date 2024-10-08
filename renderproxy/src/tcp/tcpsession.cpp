#include "tcpsession.h"
#include<iostream>
#include "tcpdatahandler.h"

#define MAX_BUFFER_LENGTH 64*1024

TCPSession::TCPSession(boost::asio::io_context& ioc) :m_socket(ioc)
{
	m_pBuffer = new char[MAX_BUFFER_LENGTH];
	m_pHandler = new TCPDataHandler();
}

TCPSession::~TCPSession()
{
	if (m_pBuffer) {
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
	if (m_pHandler) {
		delete m_pHandler;
		m_pHandler = NULL;
	}
}

boost::asio::ip::tcp::socket& TCPSession::getSocket()
{
	return m_socket;
}

void TCPSession::start()
{
	//memset(m_pBuffer, 0, sizeof(m_pBuffer));
	m_socket.async_read_some(boost::asio::buffer(m_pBuffer, MAX_BUFFER_LENGTH), std::bind(&TCPSession::handleReceive, this, std::placeholders::_1, std::placeholders::_2));

}

void TCPSession::handleReceive(const::boost::system::error_code& error, size_t received_len)
{
	if (!error)
	{
		//std::cout << "TCPSession::handleReceive receive data length: " << received_len << std::endl;
		//m_socket.async_write_some(boost::asio::buffer(m_pBuffer, received_len), std::bind(&TCPSession::handleSend, this, std::placeholders::_1));
		m_pHandler->handleData(m_pBuffer, received_len);

		//continue to read next...
		m_socket.async_read_some(boost::asio::buffer(m_pBuffer, MAX_BUFFER_LENGTH), std::bind(&TCPSession::handleReceive, this, std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		delete this;
	}
}

void TCPSession::handleSend(const::boost::system::error_code& error)
{
	if (!error)
	{
	}
	else
	{
		std::cout << "TCPSession::handleSend send data error: " << error.to_string() << std::endl;
		delete this;
	}
}
