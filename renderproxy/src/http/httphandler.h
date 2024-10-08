#pragma once
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class HttpHandler : public std::enable_shared_from_this<HttpHandler>
{
public:
    std::shared_ptr<HttpHandler> get()
    {
        return shared_from_this();
    }

    HttpHandler(tcp::socket socket);

    // Initiate the asynchronous operations associated with the connection.
    void start();
private:
    // The socket for the currently connected client.
    tcp::socket socket_;

    // The buffer for performing reads.
    beast::flat_buffer buffer_{ 8192 };

    // The request message.
    http::request<http::dynamic_body> request_;

    // The response message.
    http::response<http::dynamic_body> response_;

    // The timer for putting a deadline on connection processing.
    net::steady_timer deadline_{
        socket_.get_executor(), std::chrono::seconds(60) };

    //void loop(tcp::acceptor& acceptor);

    // Asynchronously receive a complete request message.
    void readRequest();

    // Determine what needs to be done with the request message.
    void processRequest();

    // Construct a response message based on the program state.
    void createResponse();

    // Asynchronously transmit the response message.
    void writeResponse();

    // Check whether we have spent enough time on this connection.
    void checkDeadline();
    void createPostResponse();
};