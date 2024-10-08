#include "net/tcplink.h"
#include<boost/asio.hpp>

#include <QApplication>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "yangplayer/OpenGLPlayer.h"
#include "mainwindow.h"
#include "video/yangrecordthread.h"
#include <QScreen>

#ifdef _HAS_STD_BYTE
#undef _HAS_STD_BYTE
#endif
#define _HAS_STD_BYTE 0

void test_thread_function(MainWindow* w) {
	std::cout << "Hello from thread!" << std::endl;
	std::string filename = "test.yuv";
	uint32_t width = 320;
	uint32_t height = 240;

	uint8_t* data = new uint8_t[width * height * 3 / 2];
	std::ifstream fin(filename, std::ios::in | std::ios::binary);
	while (true) {
		if (fin.eof()) {
			fin.seekg(0, std::ios::beg);
		}
		fin.read((char*)data, width * height * 3 / 2);
		w->playVideo(data, width, height);
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
	delete[] data;
	fin.close();
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	boost::asio::io_context ioc;
	TCPLink tcpLink(ioc);

	MainWindow w(&tcpLink);

	YangRecordThread videoThread;
	w.m_videoThread = &videoThread;
	w.initVideoThread(&videoThread);
	//获取主屏幕
	QScreen* screen = QApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	// 计算窗口左上角坐标以使其居中
	int x = (screenGeometry.width() - w.width()) / 2;
	int y = (screenGeometry.height() - w.height()) / 2;
	// 移动窗口到计算出的坐标
	w.move(200, 200);
	videoThread.start();
	w.showFullScreen();
	//w.show();

	////test code
	//std::thread my_thread(test_thread_function, &w);
	//my_thread.detach();

	return a.exec();
}