#include "CubeForm.h"
#include "GLGeometry.h"

CubeForm::CubeForm(HINSTANCE hin)
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

CubeForm::~CubeForm(void)
{
}

void CubeForm::OnCreate()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);

    m_cube1.Init();
    m_cube1.SetSize(0.5);
    m_cube1.SetColor(TG::Color32(0, 0, 255), TG::Color32(0, 255, 0), TG::Color32(255, 0, 0), 
        TG::Color32(255, 255, 0), TG::Color32(255, 0, 255), TG::Color32(0, 255, 255));

    m_cube2.Init();
    m_cube2.SetSize(0.5);
    m_cube2.SetColor(TG::Color32(0, 0, 255), TG::Color32(0, 255, 0), TG::Color32(255, 0, 0), 
        TG::Color32(255, 255, 0), TG::Color32(255, 0, 255), TG::Color32(0, 255, 255));
}

void CubeForm::OnSize(int w, int h)
{
    printf("OnSize: %d, %d\n", w, h);
}

float s_x_step;
void CubeForm::OnDraw()
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

void CubeForm::OnKeyDown(GLKeyEventArgsPtr key_args)
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
    Draw3d();
}

void CubeForm::OnMouseDown(GLMouseEventArgsPtr args)
{
    if (args->IsLeft()) {
        m_drag_x = 0;
        m_drag_y = 0;
        m_drag.SetStartPoint(m_drag_x, m_drag_y);
        m_drag.MouseDown(args->m_location);
    }
}

void CubeForm::OnMouseMove(GLMouseEventArgsPtr args)
{
    if (m_drag.IsMouseDown()) {
        TG::PointInt p = m_drag.MouseMove(args->m_location);
        //double a = asin(p.m_y * 1.6 / 3.3);
        //printf("Mouse: %d\n", a);

        float nx = 90*p.m_x*6 / Width();
        float ny = 90*p.m_y*6 / Height();
        m_cube1.RotateY(nx-m_drag_x, 0, 0, 0);
        m_cube1.RotateX(ny-m_drag_y, 0, 0, 0);
        m_drag_x = nx;
        m_drag_y = ny;

        Draw3d();
    }
}

void CubeForm::OnMouseUp(GLMouseEventArgsPtr args)
{
    m_drag.MouseUp();
}
