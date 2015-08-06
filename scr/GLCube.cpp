#include "GLCube.h"

GLCube::GLCube(void)
: m_obj_style(GLObjQuad),
m_size(2),
m_want_compile(true)
{
    //默认都是白色
    for (int i = 0; i < 6; ++i) {
        m_colors[i] = TG::Color32::s_White;
    }
}

GLCube::~GLCube(void)
{
    return;
}

void GLCube::Init()
{
    m_list = glGenLists(1);
}

void GLCube::SetSize(double size)
{
    m_size = size;
    //Compile();
    m_want_compile = true;
}

void GLCube::SetPosition(float x, float y, float z)
{
    m_position.SetValue(x, y, z);
}

void GLCube::SetRotateMid(float x, float y, float z)
{
    m_rotate_origin.SetValue(x, y, z);
}

void GLCube::SetColor(int index, TG::Color32 &color)
{
    if (index >= 0 && index <= 5) {
        m_colors[index] = color;
    }
    m_want_compile = true;
}

void GLCube::SetColor(TG::Color32 &c0, TG::Color32 &c1, TG::Color32 &c2,
        TG::Color32 &c3, TG::Color32 &c4, TG::Color32 &c5)
{
    m_colors[0] = c0;
    m_colors[1] = c1;
    m_colors[2] = c2;
    m_colors[3] = c3;
    m_colors[4] = c4;
    m_colors[5] = c5;

    m_want_compile = true;
}

void GLCube::SetAllColor(TG::Color32 &color)
{
    m_colors[0] = color;
    m_colors[1] = color;
    m_colors[2] = color;
    m_colors[3] = color;
    m_colors[4] = color;
    m_colors[5] = color;

    m_want_compile = true;
}

void GLCube::SetObjStyle(GLObjStyle style)
{
    m_obj_style = style;
    m_want_compile = true;
}

void GLCube::Draw()
{
    if (m_want_compile) {
        Compile();
        m_want_compile = false;
    }
    const GLfloat *p = *m_matrix.m;

    glPushMatrix();
    {
        glMultMatrixf(p);
        glTranslatef(m_position.m_x, m_position.m_y, m_position.m_z);
        glCallList(m_list);
    }
    glPopMatrix();
}

void GLCube::TranOrigin(float x, float y, float z)
{
    m_matrix.Translate(-x, -y, -z);
}

void GLCube::RetnOrigin(float x, float y, float z)
{
    m_matrix.Translate(x, y, z);
}

void GLCube::RotateX(float ang, float x, float y, float z)
{
    TranOrigin(x, y, z);
    m_matrix.RotateX(ang);
    RetnOrigin(x, y, z);
}

void GLCube::RotateY(float ang, float x, float y, float z)
{
    TranOrigin(x, y, z);
    m_matrix.RotateY(ang);
    RetnOrigin(x, y, z);
}

void GLCube::RotateZ(float ang, float x, float y, float z)
{
    TranOrigin(x, y, z);
    m_matrix.RotateZ(ang);
    RetnOrigin(x, y, z);
}

void GLCube::SetDrawColor(int i)
{
    if (m_obj_style == GLObjQuad) {
        if (i >= 0 && i <= 5) {
            glColor4ub(m_colors[i].m_r, m_colors[i].m_g, m_colors[i].m_b, m_colors[i].m_a);
        }
    } else if (m_obj_style == GLObjLine) {
        if (i == 0) {
            glColor4ub(m_colors[i].m_r, m_colors[i].m_g, m_colors[i].m_b, m_colors[i].m_a);
        }
    }
}

void GLCube::Compile()
{
    glNewList(m_list, GL_COMPILE);

    {
        double size = m_size*0.5;
#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

        {
            int gl_style = GL_QUADS;
            if (m_obj_style == GLObjLine) {
                gl_style = GL_LINE_LOOP;
            }
            glBegin(gl_style);
            SetDrawColor(0);
            N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
            glEnd();

            glBegin(gl_style);
            SetDrawColor(1);
            N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); 
            glEnd();

            glBegin(gl_style);
            SetDrawColor(2);
            N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); 
            glEnd();

            glBegin(gl_style);
            SetDrawColor(3);
            N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); 
            glEnd();

            glBegin(gl_style);
            SetDrawColor(4);
            N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); 
            glEnd();

            glBegin(gl_style);
            SetDrawColor(5);
            N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); 
            glEnd();
        }
#   undef V
#   undef N
    }

    glEndList();
}
