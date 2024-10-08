#include "tcplink.h"
#include "inputcmd.pb.h"
#include <QDebug>
#include "json/json.h"
#include "util/jsonutil.h"

TCPLink::TCPLink(boost::asio::io_context& ioc)
    : m_socket(ioc)
{
    boost::asio::ip::tcp::endpoint ed(boost::asio::ip::address::from_string("192.168.2.108"), 5200);
    m_socket.connect(ed);
}

//key event: {"type","0", "action":"0", "keycode":70, "keyname":'F',}
//mouse event: {"type","1", "action":"0", x:"0.2604", y:'0.2604',} x/screen.width, y/screen.height

void TCPLink::sendKeyEvent(int type, int code, QString name)
{
    Json::Value cmd;
    cmd["type"] = Json::Value(render::CMDType::CMD_KEY);
    cmd["action"] = type == 20 ? Json::Value(render::KeyActionType::KEY_DOWN) : Json::Value(render::KeyActionType::KEY_UP);
    cmd["keycode"] = Json::Value(code);
    cmd["keyname"] = Json::Value(name.toStdString());
    std::string strJson = JsonUtil::toString(cmd);

    std::string str;
    render::CMDMessage msg;
    msg.set_content(strJson);
    msg.SerializeToString(&str);
    send(str.c_str(), str.length());
    qDebug()<<"sendKeyEvent: type:"<<type<<", content:"<<strJson << ", length: "<<str.length();
}

void TCPLink::sendMouseEvent(int type, int x, int y)
{

}

void TCPLink::send(const char* buf, const int length)
{
    try {
        m_socket.send(boost::asio::buffer(buf, length));

        // char rec[10240] = "";
        // m_socket.receive(boost::asio::buffer(rec, 10240));

        // render::CMDMessage msg;
        // msg.ParseFromString(rec);

        // std::map<std::string, Json::Value> values = JsonUtil::fromString(msg.content());
        // qDebug()<<"receive data length: "<< sizeof(rec) <<", content: "<<msg.content();

    } catch (const std::exception& ex) {
        qDebug() << "Exception: " << ex.what();
    }

}
