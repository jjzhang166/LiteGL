#include <Windows.h>

#include "LnWin/LConsole.hpp"
#include "TextureForm.h"


int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd)
{
    TextureForm frm(hInstance);
    frm.SetAppStyle(GLApp2D);
    GLAppRun(&frm);

    return 0;
}






