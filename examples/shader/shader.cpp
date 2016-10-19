#include <Windows.h>
#include <stdio.h>
#include "ShaderForm.h"
#include "LnWin/LConsole.hpp"
#include "LnImg/LBitmap.h"

int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd)
{
    /*ln::LBitmap bmp;
    bmp.ReadBmp(L"D:\\512.bmp");
    bmp.Conver8To32();
    bmp.WriteBmp(L"D:\\z_bit8.bmp");*/

    ShaderForm *frm = new ShaderForm(hInstance);
    frm->SetAppStyle(GLApp2D);
    GLAppRun(frm);

    return 0;
}

//int main(int argc, char** argv)
//{
//    HWND hwnd = GetConsoleHwnd();
//    PIXELFORMATDESCRIPTOR pfd;
//    pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
//    pfd.nVersion   = 1;
//    pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
//    pfd.iPixelType = PFD_TYPE_RGBA;
//    pfd.cColorBits = 16;
//    pfd.cDepthBits = 16;
//
//    HDC dc = ::GetDC(hwnd);
//    GLuint pixel_format = ChoosePixelFormat(dc, &pfd);
//    SetPixelFormat(dc, pixel_format, &pfd);
//    HGLRC context = wglCreateContext(dc);
//
//
//    GLenum err = glewInit();
//    printf("after: %d \n", __glewCreateShader);
//    AddShaderPrograme();
//
//    return 0;
//}

