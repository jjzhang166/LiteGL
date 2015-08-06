#pragma once

#include "TGBitmap.h"
#include "LnWin/LString.h"

bool GLLoadImage(const wchar_t *filename, int *width, int *height, unsigned char *&p_data);

//ָʾGL������2d��ʾ����3d��ʾ, Ĭ��Ϊ3d
enum GLAppStyle
{
    GLApp2D,    //2d��Ӧƽ��ͶӰ
    GLApp3D     //3d��Ӧ͸��ͶӰ
};

//ָʾ�������߿���ʾ���������ʾ
enum GLObjStyle
{
    GLObjLine,  //�߿�
    GLObjQuad   //���
};
