#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include "GLUtility.h"
#include "Matrix3d.h"

//正方体
class GLCube
{
public:
    GLCube(void);
    ~GLCube(void);
    
    void Init();

    void SetSize(double size);
    void SetPosition(float x, float y, float z);

    //设置绕哪个点进行旋转
    void SetRotateMid(float x, float y, float z);

    void SetColor(int index, TG::Color32 &color);
    void SetColor(TG::Color32 &c0, TG::Color32 &c1, TG::Color32 &c2,
        TG::Color32 &c3, TG::Color32 &c4, TG::Color32 &c5);
    void SetObjStyle(GLObjStyle style);

    void Draw();

    void RotateX(float ang);
    void RotateY(float ang);
    void RotateZ(float ang);

private:
    void Compile();
    void SetDrawColor(int i);
    void TranOrigin();
    void RetnOrigin();

private:
    GLObjStyle m_obj_style;
    GLfloat m_size;
    TG::Color32 m_colors[6];

    GLuint m_list;
    bool m_want_compile;

    Matrix3d m_matrix;

    Point3dFloat m_position;
    Point3dFloat m_rotate_origin;
};
