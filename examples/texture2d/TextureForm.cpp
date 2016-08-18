#define GLEW_STATIC
#include "GL/glew.h"
#include "TextureForm.h"
#include "GLUtility.h"

TextureForm::TextureForm(HINSTANCE hin)
: GLForm(hin)
{
}

TextureForm::~TextureForm(void)
{
}


void TextureForm::OnCreate()
{
    //printf("before: %d \n", __glewCreateShader);


    {
        int width, height;
        unsigned char *data;
        GLLoadImage(L"D:\\2.png", &width, &height, data);
        m_img1.Init(width, height, data);
        delete data;
    }
    {
        int width, height;
        unsigned char *data;
        GLLoadImage(L"D:\\g.jpg", &width, &height, data);
        m_img2.Init(width, height, data);
        delete data;
    }

}

void TextureForm::OnDraw()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);

    m_img1.Draw();
    m_img2.Draw();
}

void TextureForm::OnSize(int w, int h)
{
    m_img1.WinSize(w, h);
    m_img2.WinSize(w, h);

    m_img2.SetPos(w-m_img2.Width(), h-m_img2.Height());
    //m_img1.SetPos((w-m_img1.Width())/2, (h-m_img1.Height())/2);
    //m_img1.RefreshBuffer(offx, offy);

    printf("OnSize: %d, %d\n", w, h);
}

void TextureForm::OnKeyDown(GLKeyEventArgsPtr key_args)
{
    int left = m_img1.Left();
    int top = m_img1.Top();
    switch(key_args->m_vk_code) {
        case VK_LEFT:
            m_img1.SetPos(left-1, top);
            break;

        case VK_RIGHT:
            m_img1.SetPos(left+1, top);
            break;

        case VK_UP:
            m_img1.SetPos(left, top-1);
            break;

        case VK_DOWN:
            m_img1.SetPos(left, top+1);
            break;
    }
    Repaint();
   
}

void TextureForm::OnMouseDown(GLMouseEventArgsPtr args)
{

    m_drag.SetStartPoint(m_img1.Left(), m_img1.Top());
    m_drag.MouseDown(args->m_location);
}

void TextureForm::OnMouseMove(GLMouseEventArgsPtr args)
{
    if (m_drag.IsMouseDown()) {
        ln::PointInt p = m_drag.MouseMove(args->m_location);
        m_img1.SetPos(p.m_x, p.m_y);
        Repaint();
    }
}

void TextureForm::OnMouseUp(GLMouseEventArgsPtr args)
{

    m_drag.MouseUp();
}
