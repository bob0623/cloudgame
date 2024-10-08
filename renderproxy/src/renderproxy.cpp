#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include "http/httphandler.h"
#include "tcp/tcpserver.h"
#include "renderbase/log/logger.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

void httpRequestloop(tcp::acceptor& acceptor)
{
    acceptor.async_accept(
        [&](beast::error_code ec, tcp::socket soc)
    {
        if (!ec)
            std::make_shared<HttpHandler>(std::move(soc))->start();
        httpRequestloop(acceptor);
    });
}

void initLog() {
    xlog::InitInfo info;
    info.log_mode = xlog::InitInfo::LOG_MODE_SYNC;
    info.log_dir = "./";
    info.log_store_file_num = 4;
    info.log_max_size_MB = 5;
    xlog::init(info);
}


int main(int argc, char* argv[])
{
    try
    {
        initLog();
        //http server start
        auto const address = net::ip::make_address("127.0.0.1");
        unsigned short port = static_cast<unsigned short>(8080);
        net::io_context ioc{ 2 };

        tcp::acceptor acceptor{ ioc, { address, port } };
        httpRequestloop(acceptor);
        //http server end.

        //tcp server start
        TCPServer tcpsrv(ioc, 5200);
        //tcp server end.

        ioc.run();

    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

