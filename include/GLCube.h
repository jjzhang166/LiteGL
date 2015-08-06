#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include "GLUtility.h"
#include "Matrix3d.h"

//Õý·½Ìå
class GLCube
{
public:
    GLCube(void);
    ~GLCube(void);
    
    void Init();
    void SetSize(double size);
    void SetColor(int index, TG::Color32 &color);
    void SetColor(TG::Color32 &c0, TG::Color32 &c1, TG::Color32 &c2,
        TG::Color32 &c3, TG::Color32 &c4, TG::Color32 &c5);
    void SetObjStyle(GLObjStyle style);

    void Draw();

    void RotateX(float ang, float x, float y, float z);
    void RotateY(float ang, float x, float y, float z);
    void RotateZ(float ang, float x, float y, float z);

private:
    void Compile();
    void SetDrawColor(int i);

private:
    GLObjStyle m_obj_style;
    GLfloat m_size;
    TG::Color32 m_colors[6];

    GLuint m_list;
    bool m_want_compile;

    Matrix3d m_matrix;
};
