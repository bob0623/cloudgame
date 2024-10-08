#ifndef TCPLINK_H
#define TCPLINK_H

#include "singleton.h"
#include<boost/asio.hpp>
#include<iostream>
#include <QObject>


class TCPLink : public QObject
{
    Q_OBJECT
public:
    TCPLink(boost::asio::io_context& ioc);
    ~TCPLink(){};
public:
    Q_INVOKABLE void sendKeyEvent(int type, int code, QString name);
    Q_INVOKABLE void sendMouseEvent(int type, int x, int y);
    Q_INVOKABLE void send(const char* buf, const int length);

private:
    boost::asio::ip::tcp::socket m_socket;
};

#endif // TCPLINK_H
