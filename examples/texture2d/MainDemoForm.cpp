#include "DemoForm.h"
#include "GLUtility.h"

DemoForm::DemoForm(HINSTANCE hin)
: GLForm(hin)
{
}

DemoForm::~DemoForm(void)
{
}

void DemoForm::OnCreate()
{
    {
        int width, height;
        unsigned char *data;
        GLLoadImage(L"D:\\sh.png", &width, &height, data);
        m_img1.Init(width, height, data);
        delete data;
    }
    {
        int width, height;
        unsigned char *data;
        GLLoadImage(L"D:\\aiqt.jpg", &width, &height, data);
        m_img2.Init(width, height, data);
        delete data;
    }

}

void DemoForm::OnDraw()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);

    m_img1.Draw();
    m_img2.Draw();
}

void DemoForm::OnSize(int w, int h)
{
    m_img1.WinSize(w, h);
    m_img2.WinSize(w, h);

    m_img2.SetPos(w-m_img2.Width(), h-m_img2.Height());
    //m_img1.SetPos((w-m_img1.Width())/2, (h-m_img1.Height())/2);
    //m_img1.RefreshBuffer(offx, offy);

    printf("OnSize: %d, %d\n", w, h);
}

void DemoForm::OnKeyDown(GLKeyEventArgsPtr key_args)
{
    int left = m_img1.Left();
    int top = m_img1.Top();
    switch(key_args->m_vk_code) {
        case VK_LEFT:
            m_img1.SetPos(left-1, top);
            Draw3d();
            break;

        case VK_RIGHT:
            m_img1.SetPos(left+1, top);
            Draw3d();
            break;

        case VK_UP:
            m_img1.SetPos(left, top-1);
            Draw3d();
            break;

        case VK_DOWN:
            m_img1.SetPos(left, top+1);
            Draw3d();
            break;
    }
   
}

void DemoForm::OnMouseDown(GLMouseEventArgsPtr args)
{

    m_drag.SetStartPoint(m_img1.Left(), m_img1.Top());
    m_drag.MouseDown(args->m_location);
}

void DemoForm::OnMouseMove(GLMouseEventArgsPtr args)
{
    if (m_drag.IsMouseDown()) {
        TG::PointInt p = m_drag.MouseMove(args->m_location);
        m_img1.SetPos(p.m_x, p.m_y);
        Draw3d();
    }
}

void DemoForm::OnMouseUp(GLMouseEventArgsPtr args)
{

    m_drag.MouseUp();
}
