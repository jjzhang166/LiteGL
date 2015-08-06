#include "GLWidget.h"

GLWidget::GLWidget(void)
: m_texture_id(0),
m_left(0), m_top(0),
m_width(0), m_height(0)
{
}

GLWidget::~GLWidget(void)
{
}

void GLWidget::Init(int w, int h, unsigned char *data)
{
    m_width = w;
    m_height = h;

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
        GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);

    RefreshBuffer(0, 0);
}

void GLWidget::WinSize(int w, int h)
{
    m_win_width = w;
    m_win_height = h;

    double offx, offy;
    if (w % 2 == 0) {
        offx = -0.5;
    } else {
        offx = 0;
    }
    if (h % 2 == 0) {
        offy = -0.5;
    } else {
        offy = 0;
    }

    RefreshBuffer(offx, offy);
}

void GLWidget::SetSize(int w, int h)
{
    m_width = w;
    m_height = h;
}

void GLWidget::SetPos(int left, int top)
{
    m_left = left;
    m_top = top;
}

int GLWidget::Width() const
{
    return m_width;
}

int GLWidget::Height() const
{
    return m_height;
}

int GLWidget::Left() const
{
    return m_left;
}

int GLWidget::Top() const
{
    return m_top;
}

void GLWidget::RefreshBuffer(double offx, double offy)
{
    double half_width = m_width/2.0;
    double half_height = m_height/2.0;

    double x1 = -half_width + offx;
    double y1 = -half_height + offy;
    double x2 = x1 + m_width;
    double y2 = y1 + m_height;

    m_ver_buffer.Create(4);
    m_ver_buffer.SetAt(0, x1, y2, 0, 0, 1);
    m_ver_buffer.SetAt(1, x1, y1, 0, 0, 0);
    m_ver_buffer.SetAt(2, x2, y1, 0, 1, 0);
    m_ver_buffer.SetAt(3, x2, y2, 0, 1, 1);
}

void GLWidget::Draw()
{
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glLoadIdentity();
    glTranslatef(GetMidX(), GetMidY(), 0);
    m_ver_buffer.DrawVertexBuffer(GL_QUADS);
}

int GLWidget::GetMidX()
{
    //return m_left + m_width/2.0;
    //return m_left;
    return (m_width-m_win_width)/2.0 + m_left;
}

int GLWidget::GetMidY()
{
    //return m_top + m_height/2.0;
    //return -m_top;
    return (-m_win_height+m_height)/2.0 + m_top;
}