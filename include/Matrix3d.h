#pragma once
#include <math.h>

static const float pi = 3.141592653589793;
class Matrix3d
{
public:
    Matrix3d();
    //Matrix3d(const float *matrix);
    Matrix3d(float _11, float _12, float _13, float _14,
        float _21, float _22, float _23, float _24,
        float _31, float _32, float _33, float _34, 
        float _41, float _42, float _43, float _44);
    ~Matrix3d(void);

    void SetValue(float _11, float _12, float _13, float _14,
        float _21, float _22, float _23, float _24,
        float _31, float _32, float _33, float _34, 
        float _41, float _42, float _43, float _44);

    Matrix3d operator * (const Matrix3d&) const;

    void Translate(float x, float y, float z);

    void RotateX(float ang);
    void RotateY(float ang);
    void RotateZ(float ang);

    void Identity();



public:
    union {
        struct {
            float m_11, m_12, m_13, m_14;
            float m_21, m_22, m_23, m_24;
            float m_31, m_32, m_33, m_34;
            float m_41, m_42, m_43, m_44;
        };
        float m[4][4];
    };
}; // end class Matrix3d

inline float CrossMultiply4(const float *horize, const float *vertical);

inline void GetRow(float *row, const Matrix3d *mat, const int index);

inline void GetCol(float *col, const Matrix3d *mat, const int index);

