#pragma once

#include <Windows.h>
#include <gl\GL.h>
#include "GLVertexBuffer.h"

class GLWidget
{
public:
    GLWidget(void);
    ~GLWidget(void);

    void Init(int w, int h, unsigned char *data);
    void WinSize(int w, int h);


    void SetSize(int w, int h);
    void SetPos(int left, int top);

    int Width() const;
    int Height() const;
    int Left() const;
    int Top() const;

    void Draw();

private:
    int GetMidX();
    int GetMidY();

    void RefreshBuffer(double offx, double offy);

private:
    GLuint m_texture_id;
    GLVertexBuffer m_ver_buffer;

    int m_left;
    int m_top;

    int m_width;
    int m_height;

    int m_win_width;
    int m_win_height;
};
