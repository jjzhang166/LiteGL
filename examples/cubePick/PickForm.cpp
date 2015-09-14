#include "PickForm.h"
#include "GLGeometry.h"

PickForm::PickForm(HINSTANCE hin)
: GLForm(hin),
m_rot_x(0),
m_rot_y(0),
m_rot_z(0),
m_drag_x(0),
m_drag_y(0),
m_look_z(0)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

PickForm::~PickForm(void)
{
}

void PickForm::OnCreate()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);

    m_cube1.Init();
    m_cube1.SetSize(0.5);
    m_cube1.SetColor(ln::Color32(0, 0, 255), ln::Color32(0, 255, 0), ln::Color32(255, 0, 0), 
        ln::Color32(255, 255, 0), ln::Color32(255, 0, 255), ln::Color32(0, 255, 255));

    m_cube2.Init();
    m_cube2.SetSize(0.5);
    m_cube2.SetColor(ln::Color32(0, 0, 255), ln::Color32(0, 255, 0), ln::Color32(255, 0, 0), 
        ln::Color32(255, 255, 0), ln::Color32(255, 0, 255), ln::Color32(0, 255, 255));
}

void PickForm::OnSize(int w, int h)
{
    printf("OnSize: %d, %d\n", w, h);

    glViewport(0, 0, w, h); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

float s_x_step;
void PickForm::OnDraw()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //TODO:这里应该得自己来算矩阵
    //glMultMatrixd();
    glRotatef(m_rot_x, 0, 0, -1);
    //glRotatef(m_drag_y, 1, 0, 0);
    //glRotatef(m_drag_x, 0, 1, 0);

    /*glPushMatrix();
    glCallList(m_cubelist);
    glPopMatrix();*/
    m_cube1.Draw();

    s_x_step = 0.5+5.0/Width();
    glTranslatef(s_x_step, 0, 0);
    m_cube2.Draw();

    //强制绘制,可以不用
    glFlush();
}

void PickForm::OnKeyDown(GLKeyEventArgsPtr key_args)
{
    int one = 10;
    switch (key_args->m_vk_code) {
        case VK_LEFT:
            //m_rot_x -= one;
            m_cube2.RotateX(one,  -s_x_step,0, 0);
            break;

        case VK_RIGHT:
            //m_rot_x += one;
            m_cube2.RotateX(-one,  s_x_step,0, 0);
            break;

        case VK_UP:
            m_rot_y -= one;
            m_cube2.RotateY(one, -s_x_step, 0, 0);
            break;

        case VK_DOWN:
            m_rot_y += one;
            m_cube2.RotateY(-one, -s_x_step, 0, 0);
            break;

        case 'E':
            m_rot_z -= one;
            //m_look_z -= 0.5;
            break;

        case 'D':
            m_rot_z += one;
            //m_look_z += 0.5;
            break;
    }
    Repaint();
}

void PickForm::OnMouseDown(GLMouseEventArgsPtr args)
{
    if (args->IsLeft()) {
        m_drag_x = 0;
        m_drag_y = 0;
        m_drag.SetStartPoint(m_drag_x, m_drag_y);
        m_drag.MouseDown(args->m_location);
    }
}

void PickForm::OnMouseMove(GLMouseEventArgsPtr args)
{
    if (m_drag.IsMouseDown()) {
        ln::PointInt p = m_drag.MouseMove(args->m_location);
        //double a = asin(p.m_y * 1.6 / 3.3);
        //printf("Mouse: %d\n", a);

        float nx = 90*p.m_x*6 / Width();
        float ny = 90*p.m_y*6 / Height();
        m_cube1.RotateY(nx-m_drag_x, 0, 0, 0);
        m_cube1.RotateX(ny-m_drag_y, 0, 0, 0);
        m_drag_x = nx;
        m_drag_y = ny;

        Repaint();
    }
}

void PickForm::OnMouseUp(GLMouseEventArgsPtr args)
{
    m_drag.MouseUp();
}
