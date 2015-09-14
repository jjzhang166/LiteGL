#include "Matrix3d.h"


float CrossMultiply4(const float *horize, const float *vertical)
{
    return horize[0]*vertical[0] +
        horize[1]*vertical[1] +
        horize[2]*vertical[2] +
        horize[3]*vertical[3];
}

void GetRow(float *row, const Matrix3d *mat, const int index)
{
    row[0] = mat->m[index][0];
    row[1] = mat->m[index][1];
    row[2] = mat->m[index][2];
    row[3] = mat->m[index][3];
}

void GetCol(float *col, const Matrix3d *mat, const int index)
{
    col[0] = mat->m[0][index];
    col[1] = mat->m[1][index];
    col[2] = mat->m[2][index];
    col[3] = mat->m[3][index];
}


Matrix3d::Matrix3d()
{
    m_11 = m_12 = m_13 = m_14
        = m_21 = m_22 = m_23 = m_24 
        = m_31 = m_32 = m_33 = m_34
        = m_41 = m_42 = m_43 = m_44 = 0;
    m_11 = m_22 = m_33 = m_44 = 1;
}



Matrix3d::Matrix3d(float _11, float _12, float _13, float _14,
                   float _21, float _22, float _23, float _24,
                   float _31, float _32, float _33, float _34, 
                   float _41, float _42, float _43, float _44)
{
    this->m_11 = _11;this->m_12 = _12;this->m_13 = _13;this->m_14 = _14;
    this->m_21 = _21;this->m_22 = _22;this->m_23 = _23;this->m_24 = _24;
    this->m_31 = _31;this->m_32 = _32;this->m_33 = _33;this->m_34 = _34;
    this->m_41 = _41;this->m_42 = _42;this->m_43 = _43;this->m_44 = _44;
}

Matrix3d::~Matrix3d(void)
{
}

void Matrix3d::Identity()
{
    m_11 = m_12 = m_13 = m_14
        = m_21 = m_22 = m_23 = m_24 
        = m_31 = m_32 = m_33 = m_34
        = m_41 = m_42 = m_43 = m_44 = 0;
    m_11 = m_22 = m_33 = m_44 = 1;
}

void Matrix3d::SetValue(float _11, float _12, float _13, float _14,
                        float _21, float _22, float _23, float _24,
                        float _31, float _32, float _33, float _34, 
                        float _41, float _42, float _43, float _44)
{
    this->m_11 = _11;this->m_12 = _12;this->m_13 = _13;this->m_14 = _14;
    this->m_21 = _21;this->m_22 = _22;this->m_23 = _23;this->m_24 = _24;
    this->m_31 = _31;this->m_32 = _32;this->m_33 = _33;this->m_34 = _34;
    this->m_41 = _41;this->m_42 = _42;this->m_43 = _43;this->m_44 = _44;
}

Matrix3d Matrix3d::operator * (const Matrix3d& right) const
{
    float a1[4], a2[4], a3[4], a4[4];
    GetRow(a1, this, 0);
    GetRow(a2, this, 1);
    GetRow(a3, this, 2);
    GetRow(a4, this, 3);

    float b1[4], b2[4], b3[4], b4[4];
    GetCol(b1, &right, 0);
    GetCol(b2, &right, 1);
    GetCol(b3, &right, 2);
    GetCol(b4, &right, 3);

    Matrix3d m(
        CrossMultiply4(a1,b1),CrossMultiply4(a1,b2),CrossMultiply4(a1,b3),CrossMultiply4(a1,b4),
        CrossMultiply4(a2,b1),CrossMultiply4(a2,b2),CrossMultiply4(a2,b3),CrossMultiply4(a2,b4),
        CrossMultiply4(a3,b1),CrossMultiply4(a3,b2),CrossMultiply4(a3,b3),CrossMultiply4(a3,b4),
        CrossMultiply4(a4,b1),CrossMultiply4(a4,b2),CrossMultiply4(a4,b3),CrossMultiply4(a4,b4));

    return m;
}

void Matrix3d::Translate(float x, float y, float z)
{
    m_41 += x;
    m_42 += y;
    m_43 += z;
}

void Matrix3d::RotateX(float ang)
{
    float cos_x = cos(ang*pi/180);
    float sin_x = sin(ang*pi/180);
    Matrix3d mat(
        1 , 0      , 0     , 0   , 
        0 , cos_x  , sin_x , 0   , 
        0 , -sin_x , cos_x , 0   , 
        0 , 0      , 0     , 1);

    *this = *this * mat;
}

void Matrix3d::RotateY(float ang)
{
    float cos_y = cos(ang*pi/180);
    float sin_y = sin(ang*pi/180);
    Matrix3d mat(
        cos_y , 0 , -sin_y , 0   , 
        0     , 1 , 0      , 0   , 
        sin_y , 0 , cos_y  , 0   , 
        0     , 0 , 0      , 1);
    *this = *this * mat;
}

void Matrix3d::RotateZ(float ang)
{
    float cos_z = cos(ang*pi/180);
    float sin_z = sin(ang*pi/180);
    Matrix3d mat(
        cos_z  , sin_z , 0 , 0    , 
        -sin_z , cos_z , 0 , 0    , 
        0      , 0     , 1 , 0    , 
        0      , 0     , 0 , 1 );
    *this = *this * mat;
}

