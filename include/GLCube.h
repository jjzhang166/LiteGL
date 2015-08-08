#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <boost/shared_ptr.hpp>
#include "GLUtility.h"
#include "Matrix3d.h"

//正方体
class GLCube
{
public:
    GLCube(void);
    ~GLCube(void);
    
    void Init();
    void Draw();

    void SetObjStyle(GLObjStyle style);

    void SetSize(double size);
    void SetPosition(float x, float y, float z);

    //设置绕哪个点进行旋转
    void SetRotateMid(float x, float y, float z);

    void SetColor(int index, ln::Color32 &color);
    void SetColor(ln::Color32 &c0, ln::Color32 &c1, ln::Color32 &c2,
        ln::Color32 &c3, ln::Color32 &c4, ln::Color32 &c5);
    void SetAllColor(ln::Color32 &color);

    void RotateX(float ang, float x, float y, float z);
    void RotateY(float ang, float x, float y, float z);
    void RotateZ(float ang, float x, float y, float z);

    //如果拾取到面则返回[0,5],否则返回-1
    int Pick(int x, int y);

protected:
    virtual void Compile();

    void SetDrawColor(int i);
    void TranOrigin(float x, float y, float z);
    void RetnOrigin(float x, float y, float z);

protected:
    GLObjStyle m_obj_style;
    GLfloat m_size;
    ln::Color32 m_colors[6];

    GLuint m_list;
    bool m_want_compile;

    Matrix3d m_matrix;

    Point3dFloat m_position;
    Point3dFloat m_rotate_origin;
};

typedef boost::shared_ptr<GLCube> GLCubePtr;