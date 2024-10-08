//
// Copyright (c) 2019-2023 yanggaofeng
//

//这两个头文件必须放在最前面
#include "net/tcplink.h"
#include<boost/asio.hpp>

#include "mainwindow.h"
#include "proto/inputcmd.pb.h"

#include <yangutil/sys/YangSocket.h>
#include <yangutil/sys/YangLog.h>
#include <yangutil/sys/YangMath.h>

#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QlineEdit>
#include <QCheckBox>
#include <qevent.h>
#include <QScreen>
#include <QApplication>


MainWindow::MainWindow(TCPLink* link, QWidget* parent)
    : QMainWindow(parent)
    , m_pLink(link)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::StrongFocus);
    setGeometry(QRect(300,300, 800, 600));
    setMouseTracking(true);
    installEventFilter(this);

    m_centerWdiget=new QWidget(this);
    m_vb=new QVBoxLayout();

    setCentralWidget(m_centerWdiget);
    m_centerWdiget->setLayout(m_vb);
    // m_vb->setMargin(0);
    m_vb->setSpacing(0);
#if Yang_OS_APPLE
    m_videoWin=new YangYuvPlayWidget(this);
#else
    m_videoWin=new OpenGLPlayer(this);
    m_videoWin->SetWindow((HWND)this->winId());
#endif
    m_hb1=new QHBoxLayout();
    m_hb2=new QHBoxLayout();

    m_url = new QLabel(this);
    m_url->setText("url:");
    m_urlEdit = new QLineEdit(this);
    m_btnPlay = new QPushButton(this);
    m_btnPlay->setText("Play");
    connect(m_btnPlay, &QPushButton::clicked, this, &MainWindow::on_m_b_play_clicked, Qt::QueuedConnection);

    m_whepCheckbox = new QCheckBox(this);
    m_whepCheckbox->setText("whep");
    m_whepCheckbox->setCheckState(Qt::Unchecked);
    connect(m_whepCheckbox, &QCheckBox::checkStateChanged, this, &MainWindow::on_m_c_whep_clicked, Qt::QueuedConnection);

    m_hb1->addWidget(m_url);
    m_hb1->addWidget(m_urlEdit);
    m_hb1->addWidget(m_btnPlay);
    m_hb1->addWidget(m_whepCheckbox);
    
    m_hb2->addWidget(m_videoWin);

    //m_vb->addLayout(m_hb1);
    //暂时屏蔽顶部url输入框
    m_url->hide();
    m_urlEdit->hide();
    m_btnPlay->hide();
    m_whepCheckbox->hide();

    m_vb->addLayout(m_hb2);

    //m_vb->setStretchFactor(m_hb1,1);
    //m_vb->setStretchFactor(m_hb2,10);
    m_context=new YangContext();
    m_context->init();

    m_context->synMgr.session->playBuffer=(YangSynBuffer*)yang_calloc(sizeof(YangSynBuffer),1);//new YangSynBuffer();
    yang_create_synBuffer(m_context->synMgr.session->playBuffer);

    m_context->avinfo.sys.mediaServer=Yang_Server_Srs;//Yang_Server_Srs/Yang_Server_Zlm
    m_context->avinfo.rtc.rtcSocketProtocol=Yang_Socket_Protocol_Udp;//

    m_context->avinfo.rtc.rtcLocalPort=10000+yang_random()%15000;
    memset(m_context->avinfo.rtc.localIp,0,sizeof(m_context->avinfo.rtc.localIp));
    yang_getLocalInfo(m_context->avinfo.sys.familyType,m_context->avinfo.rtc.localIp);
    m_player= YangPlayerHandle::createPlayerHandle(m_context,this);
    yang_setLogLevel(5);
    yang_setLogFile(1);

    m_urlEdit->setText("webrtc://192.168.2.108:1985/live/livestream");
    m_isStartplay=false;

    connect(this,SIGNAL(RtcConnectFailure(int)),SLOT(connectFailure(int)));

    m_context->avinfo.rtc.iceCandidateType=YangIceHost;
    m_context->avinfo.rtc.turnSocketProtocol=Yang_Socket_Protocol_Udp;

    m_context->avinfo.rtc.enableAudioBuffer=yangtrue; //use audio buffer
    m_context->avinfo.audio.enableAudioFec=yangfalse; //srs not use audio fec
}

MainWindow::~MainWindow()
{
    if (m_pLink) {
        delete m_pLink;
        m_pLink = NULL;
    }
    m_videoThread->m_syn=NULL;
    yang_delete(m_videoWin);
    yang_delete(m_player);
    yang_closeLogFile();
    yang_delete(m_context);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    yang_trace("main window resized, width:%d, height:%d", event->size().width(), event->size().height());
    if (m_videoWin) {
        QScreen* screen = QApplication::primaryScreen();
        qreal scaleFactor = screen->devicePixelRatio();
        m_videoWin->resizeWin(event->size()* scaleFactor);
    }
}

void MainWindow::playVideo(uint8_t* data, int width, int height)
{
    m_videoWin->playVideo(data, width, height);
}

void MainWindow::success(){
}
void MainWindow::failure(int32_t errcode){
    emit RtcConnectFailure(errcode);
}
void MainWindow::connectFailure(int errcode){
    QMessageBox::about(NULL, "Error", "play error("+QString::number(errcode)+")!");
    on_m_b_play_clicked();
}
void MainWindow::initVideoThread(YangRecordThread *prt){
    m_videoThread=prt;
    m_videoThread->m_video=m_videoWin;
    m_videoThread->initPara();
    m_videoThread->m_syn= m_context->synMgr.session->playBuffer;

    on_m_b_play_clicked();
}

void MainWindow::on_m_b_play_clicked()
{
    if(!m_isStartplay){
        m_videoThread->m_syn=m_context->synMgr.session->playBuffer;
        m_videoThread->m_syn->resetVideoClock(m_videoThread->m_syn->session);
        int32_t err=Yang_Ok;
        if(m_whepCheckbox->checkState()==Qt::CheckState::Checked){
            err=m_player->playRtc(0,(char*)m_urlEdit->text().toStdString().c_str());
        }else{
            err=m_player->play((char*)m_urlEdit->text().toStdString().c_str());
        }
        if(err==Yang_Ok){
            m_btnPlay->setText("stop");

            m_isStartplay=!m_isStartplay;
            m_videoThread->m_isRender=true;
        }else{
            QMessageBox::about(NULL, "Error", "play url error!");
            m_videoThread->m_isRender=false;
        }

    }else{
        m_videoThread->m_isRender=false;
        m_btnPlay->setText("play");

        QThread::msleep(50);
        if(m_player) m_player->stopPlay();

        m_isStartplay=!m_isStartplay;

    }
}



void MainWindow::on_m_c_whep_clicked()
{
    char s[128]={0};

    if(m_whepCheckbox->checkState()==Qt::CheckState::Checked)
        sprintf_s(s,"http://%s:1985/rtc/v1/whip-play/?app=live&stream=livestream",m_context->avinfo.rtc.localIp);
    else
        sprintf_s(s,"webrtc://192.168.2.108:1985/live/livestream");

    m_urlEdit->setText(s);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    int x = event->globalPosition().x();
    int y = event->globalPosition().y();
    //qDebug() << "MainWindow mousePressEvent" << event->pos().x() << event->pos().y()<<x<<y;
    m_pLink->sendMouseEvent(render::MouseActionType::MOUSE_LEFT_DOWN, x, y);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    int x = event->globalPosition().x();
    int y = event->globalPosition().y();
    //qDebug() << "MainWindow mouseMoveEvent" << event->pos().x() << event->pos().y() << x << y;
    m_pLink->sendMouseEvent(render::MouseActionType::MOUSE_MOVE, x, y);
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    int x = event->globalPosition().x();
    int y = event->globalPosition().y();
    //qDebug() << "MainWindow mouseReleaseEvent" << event->pos().x() << event->pos().y() << x << y;
    m_pLink->sendMouseEvent(render::MouseActionType::MOUSE_LEFT_UP, x, y);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    QWidget::keyPressEvent(event);
    //qDebug() << "MainWindow keyPressEvent" << event->key() << event->text() << event->nativeScanCode() << event->nativeModifiers() << event->nativeVirtualKey();
    m_pLink->sendKeyEvent(render::KeyActionType::KEY_DOWN, event->key(), event->text());

}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    QWidget::keyReleaseEvent(event);
    //qDebug() << "MainWindow keyReleaseEvent" << event->key() << event->modifiers() << event->nativeScanCode() << event->nativeModifiers() << event->nativeVirtualKey();
    m_pLink->sendKeyEvent(render::KeyActionType::KEY_UP, event->key(), event->text());
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseMove)
    {
        auto e = dynamic_cast<QMouseEvent*>(event);
        //qDebug() << "MainWindow eventFilter MouseMove: " << e->globalPosition().x() << e->globalPosition().y();
        return true;
    }
    else if (event->type() == QEvent::HoverMove) {
        auto e = dynamic_cast<QHoverEvent*>(event);
        int x = e->globalPosition().x();
        int y = e->globalPosition().y();
        //qDebug() << "MainWindow eventFilter HoverMove: " << e->globalPosition().x() << e->globalPosition().y();
        m_pLink->sendMouseEvent(render::MouseActionType::MOUSE_MOVE, x, y);
    }
    else {
        //qDebug() << "MainWindow eventFilter" << event->type();
    }
    return    QWidget::eventFilter(watched, event);
}