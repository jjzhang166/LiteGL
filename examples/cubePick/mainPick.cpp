#include <stdlib.h>
#include "PickForm.h"
#include "LnWin/LConsole.hpp"

int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd)
{
    PickForm form(hInstance);
    form.SetStartSize(800, 822);
    GLAppRun(&form);
    return 0;
}
