#include "tcplink.h"
#include "proto/inputcmd.pb.h"
#include <QDebug>
#include "json/json.h"
#include "util/jsonutil.h"

TCPLink::TCPLink(boost::asio::io_context& ioc)
{
    m_socket = new boost::asio::ip::tcp::socket(ioc);
    boost::asio::ip::tcp::endpoint ed(boost::asio::ip::address::from_string("192.168.2.108"), 5200);
    boost::system::error_code ec;
    m_socket->connect(ed, ec);
    if (ec) {
        qDebug()<<"m_socket->connect error: "<<ec.message();
    }
    if (m_socket->is_open()) {
        qDebug() << "socket is opened."<<m_socket;
    }
    else {
        qDebug() << "socket is closed aready.";
    }
}

TCPLink::~TCPLink() 
{
    //m_socket->close();
}

//key event: {"type","0", "action":"0", "keycode":70, "keyname":'F',}
//mouse event: {"type","1", "action":"0", x:"0.2604", y:'0.2604',} x/screen.width, y/screen.height

void TCPLink::sendKeyEvent(int type, int code, QString name)
{
    Json::Value cmd;
    cmd["type"] = Json::Value(render::CMDType::CMD_KEY);
    cmd["action"] = Json::Value(type);
    cmd["keycode"] = Json::Value(code);
    cmd["keyname"] = Json::Value(name.toStdString());
    std::string strJson = JsonUtil::toString(cmd);

    render::CMDMessage msg;
    msg.set_content(strJson);
    msg.SerializeToString(&m_serialStr);
    send(m_serialStr.c_str(), m_serialStr.length());
    //qDebug()<<"sendKeyEvent: type:"<<type<<", content:"<<strJson << ", length: "<< m_serialStr.length();
}

void TCPLink::sendMouseEvent(int type, int x, int y)
{
    Json::Value cmd;
    cmd["type"] = Json::Value(render::CMDType::CMD_MOUSE);
    cmd["action"] = Json::Value(type);
    cmd["x"] = Json::Value(x);
    cmd["y"] = Json::Value(y);
    std::string strJson = JsonUtil::toString(cmd);

    render::CMDMessage msg;
    msg.set_content(strJson);
    msg.SerializeToString(&m_serialStr);
    send(m_serialStr.c_str(), m_serialStr.length());
    //qDebug() << "sendMouseEvent: type:" << type << ", content:" << strJson << ", length: " << m_serialStr.length();
}

void TCPLink::send(const char* buf, const int length)
{
    try {
        boost::system::error_code ec;
        if (!m_socket->is_open()) {
            qDebug() << "socket is closed." << m_socket;
        }
        m_socket->send(boost::asio::buffer(buf, length), 0, ec);
        if (ec) {
            qDebug() << "m_socket->send error: " << QString::fromLocal8Bit(ec.message());
        }

        // char rec[10240] = "";
        // m_socket->receive(boost::asio::buffer(rec, 10240));

        // render::CMDMessage msg;
        // msg.ParseFromString(rec);

        // std::map<std::string, Json::Value> values = JsonUtil::fromString(msg.content());
        // qDebug()<<"receive data length: "<< sizeof(rec) <<", content: "<<msg.content();

    } catch (const std::exception& ex) {
        qDebug() << "Exception: " << QString::fromLocal8Bit(ex.what());
    }

}
