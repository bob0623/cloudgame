#include "httphandler.h"

#include<json/json.h>
#include<json/value.h>
#include<json/reader.h>

namespace my_program_state
{
    std::size_t
        request_count()
    {
        static std::size_t count = 0;
        return ++count;
    }

    std::time_t
        now()
    {
        return std::time(0);
    }
}

HttpHandler::HttpHandler(tcp::socket socket)
    : socket_(std::move(socket))
{
}

void HttpHandler::start()
{
    readRequest();
    checkDeadline();
}

void HttpHandler::readRequest()
{
    auto self = shared_from_this();

    http::async_read(
        socket_,
        buffer_,
        request_,
        [self](beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);
        if (!ec)
            self->processRequest();
    });
}

void HttpHandler::processRequest()
{
    response_.version(request_.version());
    response_.keep_alive(false);

    switch (request_.method())
    {
    case http::verb::get:
        response_.result(http::status::ok);
        response_.set(http::field::server, "RenderProxy");
        createResponse();
        break;
    case http::verb::post:
        response_.result(http::status::ok);
        response_.set(http::field::server, "RenderProxy");
        createPostResponse();
        break;
    default:
        // We return responses indicating an error if
        // we do not recognize the request method.
        response_.result(http::status::bad_request);
        response_.set(http::field::content_type, "text/plain");
        beast::ostream(response_.body())
            << "Invalid request-method '"
            << std::string(request_.method_string())
            << "'";
        break;
    }

    writeResponse();
}

// Construct a response message based on the program state.
void HttpHandler::createResponse()
{
    if (request_.target() == "/count")
    {
        response_.set(http::field::content_type, "text/html");
        beast::ostream(response_.body())
            << "<html>\n"
            << "<head><title>Request count</title></head>\n"
            << "<body>\n"
            << "<h1>Request count</h1>\n"
            << "<p>There have been "
            << my_program_state::request_count()
            << " requests so far.</p>\n"
            << "</body>\n"
            << "</html>\n";
    }
    else if (request_.target() == "/time")
    {
        response_.set(http::field::content_type, "text/html");
        beast::ostream(response_.body())
            << "<html>\n"
            << "<head><title>Current time</title></head>\n"
            << "<body>\n"
            << "<h1>Current time</h1>\n"
            << "<p>The current time is "
            << my_program_state::now()
            << " seconds since the epoch.</p>\n"
            << "</body>\n"
            << "</html>\n";
    }
    else
    {
        response_.result(http::status::not_found);
        response_.set(http::field::content_type, "text/plain");
        beast::ostream(response_.body()) << "File not found\r\n";
    }
}

// Asynchronously transmit the response message.
void HttpHandler::writeResponse()
{
    auto self = shared_from_this();

    response_.content_length(response_.body().size());

    http::async_write(
        socket_,
        response_,
        [self](beast::error_code ec, std::size_t)
    {
        self->socket_.shutdown(tcp::socket::shutdown_send, ec);
        self->deadline_.cancel();
    });
}

// Check whether we have spent enough time on this connection.
void HttpHandler::checkDeadline()
{
    auto self = shared_from_this();

    deadline_.async_wait(
        [self](beast::error_code ec)
    {
        if (!ec)
        {
            // Close socket to cancel any outstanding operation.
            self->socket_.close(ec);
        }
    });
}
void HttpHandler::createPostResponse() {
    if (request_.target() == "/game")
    {
        auto& body = this->request_.body();
        auto body_str = boost::beast::buffers_to_string(body.data());
        std::cout << "receive body is " << body_str << std::endl;
        this->response_.set(http::field::content_type, "text/json");
        Json::Value root;
        Json::Reader reader;
        Json::Value src_root;
        bool parse_success = reader.parse(body_str, src_root);
        if (!parse_success) {
            std::cout << "Failed to parse JSON data!" << std::endl;
            root["error"] = 1001;
            std::string jsonstr = root.toStyledString();
            if (jsonstr.length() > 0) {
                beast::ostream(this->response_.body()) << jsonstr;
            }
            return;
        }
        auto name = src_root["name"].asString();
        std::cout << "name is " << name << std::endl;
        root["error"] = 0;
        root["name"] = src_root["name"];
        root["id"] = src_root["id"];
        root["vender"] = "Game Science";
        root["dsp"] = "WuKong is a great man.";
        std::string jsonstr = root.toStyledString();
        beast::ostream(this->response_.body()) << jsonstr;
    }
    else
    {
        response_.result(http::status::not_found);
        response_.set(http::field::content_type, "text/plain");
        beast::ostream(response_.body()) << "File not found\r\n";
    }
}