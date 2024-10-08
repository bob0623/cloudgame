#pragma once
#include<boost/asio.hpp>

class TCPDataHandler;
class TCPSession
{
public:
	TCPSession(boost::asio::io_context& ioc);
	~TCPSession();

	boost::asio::ip::tcp::socket& getSocket();
	void start();

private:
	void handleSend(const::boost::system::error_code& error);
	void handleReceive(const::boost::system::error_code& error, size_t received_len);

private:
	boost::asio::ip::tcp::socket m_socket;
	char* m_pBuffer;
	TCPDataHandler* m_pHandler;
};