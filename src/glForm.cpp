#include "GLForm.h"
#include <WindowsX.h>
#include "GLEnvironment.h"
#include "LnWin/LExplorer.h"

static GLForm* s_create_form = NULL;

static GLMouseButtons GetButton(WPARAM wp)
{
    if (wp == VK_LBUTTON) {
        return GLMouseButtons::GLMouseButton_Left;
    } else if (wp == VK_MBUTTON) {
        return GLMouseButtons::GLMouseButton_Middle;
    } else if (wp == VK_RBUTTON) {
        return GLMouseButtons::GLMouseButton_Right;
    } else if (wp == VK_XBUTTON1) {
        return GLMouseButtons::GLMouseButton_XButton1;
    } else if (wp == VK_XBUTTON2) {
        return GLMouseButtons::GLMouseButton_XButton2;
    }
    return GLMouseButtons::GLMouseButton_None;
}

void GLAppRun(GLForm *form)
{
    form->Show();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

GLForm::GLForm(HINSTANCE hin)
:
	m_instance(hin),
	m_hwnd(NULL),
	m_start_width(510),
	m_start_height(500),
	m_class_name(L"GLForm"),
	m_title_text(L"GLForm"),
	m_icon(0),
	m_is_shift_down(false),
	m_is_ctrl_down(false),
	m_is_alt_down(false),
	m_app_style(GLApp3D)
{
    m_gl_env = new GLEnvironment;
}

LRESULT GLForm::WndProcS(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
{
    if (s_create_form) {
        return s_create_form->WndProc(message, wp, lp);
    }
    return ::DefWindowProc(hwnd, message, wp, lp);
}

LRESULT GLForm::WndProc(UINT message, WPARAM wp, LPARAM lp)
{
    int x = GET_X_LPARAM(lp);
    int y = GET_Y_LPARAM(lp);
    MSG msg;

    switch (message) {
        case  WM_PAINT:
            {
                HDC hdc;
                PAINTSTRUCT ps;
                hdc = BeginPaint(m_hwnd, &ps);

                EndPaint(m_hwnd, &ps);

                Repaint();

                break;
            }

        case WM_ERASEBKGND:
            break;

        case WM_SHOWWINDOW:
            //printf("show_windows\n");
            break;
            
        case WM_CREATE:
            //printf("Create_window\n");
            break;

        case WM_SETFOCUS:
            //printf("set_focues\n");
            break;

        case WM_KILLFOCUS:
            //printf("kill_focues\n");
            break;

        case WM_TIMER:
            OnTimer(wp);
            break;

        case WM_SIZE:
            OnSize(x, y);
            m_gl_env->WinSizeChanged(x, y);
            break;

        case WM_MOUSEMOVE:
            {
                while (PeekMessage(&msg, m_hwnd, WM_MOUSEMOVE, WM_MOUSEMOVE, PM_REMOVE)) {
                    //printf("RemoveMoveMessage\n");
                }
                GLMouseButtons btn = GetButton(wp);
                GLMouseEventArgsPtr arg(new GLMouseEventArgs(btn, 1, 0, x, y, 
                    m_is_shift_down, m_is_ctrl_down, m_is_alt_down));
                OnMouseMove(arg);
                break;
            }

        case WM_MOUSEWHEEL:
            {
                RECT r;
                GetWindowRect(m_hwnd, &r);

                GLMouseButtons btn = GetButton(wp);
                GLMouseEventArgsPtr arg(new GLMouseEventArgs(GLMouseButtons::GLMouseButton_Middle, 0, GET_WHEEL_DELTA_WPARAM(wp), x-r.left, y-r.top, 
                    m_is_shift_down, m_is_ctrl_down, m_is_alt_down));
                OnMouseWheel(arg);
                break;
            }
        case WM_LBUTTONDOWN:
            {
                ::SetCapture(m_hwnd);
                GLMouseEventArgsPtr arg(new GLMouseEventArgs(GLMouseButtons::GLMouseButton_Left, 1, 0, x, y, 
                    m_is_shift_down, m_is_ctrl_down, m_is_alt_down));
                OnMouseDown(arg);
                break;
            }

        case WM_LBUTTONUP:
            {
                ::ReleaseCapture();
                GLMouseEventArgsPtr arg(new GLMouseEventArgs(GLMouseButtons::GLMouseButton_Left, 1, 0, x, y, 
                    m_is_shift_down, m_is_ctrl_down, m_is_alt_down));
                OnMouseUp(arg);
                break;
            }
        case WM_RBUTTONDOWN:
            {
                GLMouseEventArgsPtr arg(new GLMouseEventArgs(GLMouseButtons::GLMouseButton_Right, 1, 0, x, y,
                    m_is_shift_down, m_is_ctrl_down, m_is_alt_down));
                OnMouseDown(arg);
                break;
            }

        case WM_RBUTTONUP:
            {
                GLMouseEventArgsPtr arg(new GLMouseEventArgs(GLMouseButtons::GLMouseButton_Right, 1, 0, x, y,
                    m_is_shift_down, m_is_ctrl_down, m_is_alt_down));
                OnMouseUp(arg);
                break;
            }

        case WM_KEYDOWN:
            {
                if (wp == VK_SHIFT) {
                    m_is_shift_down = true;
                } else if (wp == VK_CONTROL) {
                    m_is_ctrl_down = true;
                }
                m_is_alt_down = ::GetKeyState(VK_MENU) < 0;

                GLKeyEventArgsPtr arg(new GLKeyEventArgs(wp, m_is_shift_down, m_is_ctrl_down, m_is_alt_down));
                OnKeyDown(arg);
                break;
            }
        case WM_KEYUP:
            {
                if (wp == VK_SHIFT) {
                    m_is_shift_down = false;
                } else if (wp == VK_CONTROL) {
                    m_is_ctrl_down = false;
                }
                break;
            }
        case WM_SYSKEYDOWN:
            {
                if (wp == VK_SHIFT) {
                    m_is_shift_down = true;

                } else if (wp == VK_CONTROL) {
                    m_is_ctrl_down = true;

                } 
                m_is_alt_down = ::GetKeyState(VK_MENU) < 0;

                if (wp == VK_F4 && m_is_alt_down) {
                    ::DestroyWindow(m_hwnd);
                } else {
                    GLKeyEventArgsPtr arg(new GLKeyEventArgs(wp, m_is_shift_down, m_is_ctrl_down, m_is_alt_down));
                    OnKeyDown(arg);
                }

                break;
            }

        case WM_SYSKEYUP:
            {
                if (wp == VK_SHIFT) {
                    m_is_shift_down = false;
                } else if (wp == VK_CONTROL) {
                    m_is_ctrl_down = false;
                } 
                m_is_alt_down = false;

                break;
            }

        case WM_DESTROY:
            {
                //
                //WinClose();
                //OnClose();
				//DestroyWindow(m_hwnd);
                PostQuitMessage(1);
				break;
            }

        default:
            return DefWindowProc(m_hwnd, message, wp, lp);
    }
    return 0;
}

void GLForm::Repaint()
{
    OnDraw();
    m_gl_env->Draw();
}

void GLForm::Show()
{
    if (m_hwnd == NULL) {
        CreateForm();
    }

    int cx, cy;
    ln::GetScreenSize(&cx, &cy);
    ::SetWindowPos(m_hwnd, 0, (cx-Width())/2, (cy-Height())/2, 0, 0, SWP_NOSIZE);


    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    //OnCreate();
    Repaint();
}

int GLForm::RegesterForm()
{
    static bool have_register = false;

    if (have_register) {
        return 0;
    }

    have_register = true;
    //std::wstring title = std::wstring(L"LitePaint");

    WNDCLASSEX wcex = {0};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = GLForm::WndProcS;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_instance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = m_class_name.c_str();

    if (m_icon != 0) {
        wcex.hIcon = LoadIcon(m_instance, MAKEINTRESOURCE(m_icon));
        wcex.hIconSm = LoadIcon(m_instance, MAKEINTRESOURCE(m_icon));
    }

    int r = RegisterClassEx(&wcex);

    return 0;
}

void GLForm::CreateForm()
{
    RegesterForm();

    if (m_hwnd) {
        return;
    }

    if (m_start_width == 0 || m_start_height == 0) {
        m_start_width = 500;
        m_start_height = 518;
    }
    m_hwnd = ::CreateWindowW(
        //WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT/*|WS_EX_APPWINDOW*/,
        //0x10100,
        //0,
        m_class_name.c_str(), m_title_text.c_str(), 
        //WS_MINIMIZEBOX|WS_POPUP,
        WS_OVERLAPPEDWINDOW,
        0, 0, m_start_width, m_start_height,
        NULL, NULL, m_instance, NULL);
    s_create_form = this;

    m_gl_env->InitGL(m_hwnd);
    OnCreate();
}

void GLForm::SetMinSize(int cx, int cy)
{

}

void GLForm::SetStartSize(int w, int h)
{
    m_start_width = w;
    m_start_height = h;
}

void GLForm::SetAppStyle(GLAppStyle style)
{
    m_app_style = style; 
    m_gl_env->m_app_style = style;
}

int GLForm::Width() const
{
    if (!m_hwnd) {
        return 0;
    }
    RECT rect;
    ::GetClientRect(m_hwnd, &rect);
    return rect.right;
}

int GLForm::Height() const
{
    if (!m_hwnd) {
        return 0;
    }
    RECT rect;
    ::GetClientRect(m_hwnd, &rect);
    return rect.bottom;
}

void GLForm::SetTimer(int id, unsigned int elapse)
{
    ::SetTimer(m_hwnd, id, elapse, NULL);
}

void GLForm::KillTimer(int id)
{
    ::KillTimer(m_hwnd, id);
}

void GLForm::WinClose()
{
    //delete m_gl_env;
}

void GLForm::OnDraw()
{

}

void GLForm::OnSize(int cx, int cy)
{

}

void GLForm::OnTimer(int id)
{
    
}

void GLForm::OnCreate()
{

}

void GLForm::OnClose()
{

}

void GLForm::OnKeyDown(GLKeyEventArgsPtr key_args)
{
   
}

void GLForm::OnMouseMove(GLMouseEventArgsPtr args)
{

}

void GLForm::OnMouseDown(GLMouseEventArgsPtr args)
{

}

void GLForm::OnMouseUp(GLMouseEventArgsPtr args)
{

}

void GLForm::OnMouseWheel(GLMouseEventArgsPtr args)
{

}