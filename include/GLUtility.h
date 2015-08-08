#pragma once

#include "LnImg/LBitmap.h"
#include "LnWin/LString.h"

bool GLLoadImage(const wchar_t *filename, int *width, int *height, unsigned char *&p_data);

//指示GL程序是2d显示还是3d显示, 默认为3d
enum GLAppStyle
{
    GLApp2D,    //2d对应平行投影
    GLApp3D     //3d对应透视投影
};

//指示部件是线框显示还是填充显示
enum GLObjStyle
{
    GLObjLine,  //线框
    GLObjQuad   //填充
};

template<typename T>
class BasePoint3d
{
public:
    typedef T value_type;

    BasePoint3d()
        : m_x(0), m_y(0), m_z(0)
    { }

    BasePoint3d(T x, T y, T z)
        : m_x(x) , m_y(y), m_z(0)
    { }

    template<typename T2>
    BasePoint3d(const BasePoint3d<T2> &t)
        : m_x(t.m_x), m_y(t.m_y), m_z(t.m_z)
    {
    }

    void SetValue(T x, T y, T z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    template<typename T2>
    bool IsEqual(BasePoint3d<T2> &r)
    {
        if (ln::FloatEque(m_x, r.m_x) && ln::FloatEque(m_y, r.m_y) && ln::FloatEque(m_z, r.m_z)) {
            return true;
        }
        return false;
    }

public:
    T m_x;
    T m_y;
    T m_z;
};

typedef BasePoint3d<int> Point3dInt;
typedef BasePoint3d<float> Point3dFloat;
typedef BasePoint3d<double> Point3dDouble;