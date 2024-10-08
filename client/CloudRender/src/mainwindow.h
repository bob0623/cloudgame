//
// Copyright (c) 2019-2023 yanggaofeng
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <yangplayer/OpenglPlayer.h>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QEvent>
#include <qevent.h>

#include <string>
#include "video/yangrecordthread.h"
#include "yangplayer/YangPlayerHandle.h"
#include "yangstream/YangStreamType.h"
#include "yangplayer/YangPlayWidget.h"
#include "yangplayer/YangYuvPlayWidget.h"
#include <yangutil/yangavinfotype.h>
#include <yangutil/sys/YangSysMessageI.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QPushButton;
class QLineEdit;
class QCheckBox;
class TCPLink;
class MainWindow : public QMainWindow,public YangSysMessageI
{
    Q_OBJECT
public:
    MainWindow(TCPLink* link, QWidget *parent = nullptr);
    ~MainWindow();
    YangRecordThread *m_videoThread;
    YangPlayerHandle *m_player;
#if Yang_OS_APPLE
    YangYuvPlayWidget *m_videoWin;
#else
    OpenGLPlayer *m_videoWin;
#endif

    YangStreamConfig m_conf;
    void initVideoThread(YangRecordThread *prt);

    void success();
    void failure(int32_t errcode);
    void playVideo(uint8_t* data, int width, int height);

    signals:
       void RtcConnectFailure(int errcode);
protected:
    YangContext* m_context;
    void resizeEvent(QResizeEvent* event) override;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;
private slots:
    void connectFailure(int errcode);

void on_m_b_play_clicked();

void on_m_c_whep_clicked();

private:
    QWidget *m_centerWdiget;
    QVBoxLayout *m_vb;
    QHBoxLayout *m_hb1;
    QHBoxLayout *m_hb2;
    QLabel* m_url;
    QPushButton* m_btnPlay;
    QCheckBox* m_whepCheckbox;
    QLineEdit* m_urlEdit;

    TCPLink* m_pLink;
private:
    bool m_isStartplay;

};
#endif // MAINWINDOW_H
