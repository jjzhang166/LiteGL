#pragma once

#include "TGBitmap.h"
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
