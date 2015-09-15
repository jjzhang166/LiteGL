#include <Windows.h>
#include <stdio.h>
#include "ShaderForm.h"
#include "LnWin/LConsole.hpp"
#include "LnImg/LBitmap.h"

HWND GetConsoleHwnd(void)
{
    const static int MY_BUFSIZE = 1024; // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
    char pszOldWindowTitle[MY_BUFSIZE]; // Contains original

    GetConsoleTitleA(pszOldWindowTitle, MY_BUFSIZE);

    sprintf(pszNewWindowTitle, "%d/%d",
        GetTickCount(),
        GetCurrentProcessId());

    SetConsoleTitleA(pszNewWindowTitle);

    // Ensure window title has been updated.

    Sleep(40);

    // Look for NewWindowTitle.

    hwndFound=FindWindowA(NULL, pszNewWindowTitle);

    // Restore original window title.

    SetConsoleTitleA(pszOldWindowTitle);

    return(hwndFound);
}



int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd)
{
    ln::LBitmap bmp;
    bmp.ReadBmp(L"D:\\512.bmp");
    bmp.Conver8To32();
    bmp.WriteBmp(L"D:\\z_bit8.bmp");


    ShaderForm frm(hInstance);
    frm.SetAppStyle(GLApp2D);
    GLAppRun(&frm);

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

