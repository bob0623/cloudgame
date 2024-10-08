#include<boost/asio.hpp>
#include<iostream>
int main()
{
	boost::asio::io_context ioc;
	boost::asio::ip::tcp::socket soc(ioc);
	boost::asio::ip::tcp::endpoint ed(boost::asio::ip::address::from_string("127.0.0.1"), 5200);
	char buf[1024] = "";
	try
	{
		soc.connect(ed);
		std::cout << "请输入发送的消息:";
		std::cin >> buf;
		soc.send(boost::asio::buffer(buf, strlen(buf)));
		char rec[1024] = "";
		soc.receive(boost::asio::buffer(rec, 1024));
		std::cout << "收到了消息:" << rec << std::endl;
	}
	catch (boost::system::system_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}