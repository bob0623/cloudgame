#pragma once
#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <QWidget>
#include <qevent.h>

#include <cstdint>
#include <mutex>

enum PixFormat {
    I420,
    NV12,
    NV21
};

class OpenGLPlayer : public QWidget{
    Q_OBJECT
public:
    OpenGLPlayer(QWidget* parent);

    OpenGLPlayer();
    ~OpenGLPlayer();

    void SetWindow(void* hwnd);
    void playVideo(uint8_t* data, uint32_t width, uint32_t height);
    void resizeWin(QSize size);

private:
    void Init();
    void InitContext();
    void DestroyContext();
    void InitShaders();
    void InitTexture();
    void CalcRenderPos();

signals:
    void dataUpdated();

private slots:    
    void renderOneFrame();
private:
    uint32_t window_width_{};
    uint32_t window_height_{};
    HWND hwnd_{};
    HDC hdc_{};
    HGLRC hrc_{};

    GLuint texture_y_;
    GLuint texture_u_;
    GLuint texture_v_;
    GLuint uniform_y_;
    GLuint uniform_u_;
    GLuint uniform_v_;
    GLuint shader_program_;

    uint32_t render_width_;
    uint32_t render_height_;
    uint8_t* m_pRenderData;
    std::mutex mtx;
};