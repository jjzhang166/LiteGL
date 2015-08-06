#include <Windows.h>

#include "LnWin/LConsole.hpp"
#include "DemoForm.h"


int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd)
{
    DemoForm frm(hInstance);
    frm.SetAppStyle(GLApp2D);
    //frm.Show();
    GLAppRun(&frm);

    return 0;
}






