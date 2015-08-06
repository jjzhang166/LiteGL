#include "GLEnvironment.h"

GLEnvironment::GLEnvironment(void)
	:
		m_context(NULL),
		m_dc(NULL),
		m_wnd(NULL),
        m_app_style(GLApp3D)
{
}

GLEnvironment::~GLEnvironment(void)
{
	Exit();
}


bool GLEnvironment::InitGL(HWND wnd)
{
	m_wnd = wnd;
	
	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cDepthBits = 16;
	
	m_dc = ::GetDC(m_wnd);
	GLuint pixel_format = ChoosePixelFormat(m_dc, &pfd);
	SetPixelFormat(m_dc, pixel_format, &pfd);
	m_context = wglCreateContext(m_dc);
	wglMakeCurrent(m_dc, m_context);

	RECT rect;
    ::GetClientRect(m_wnd, &rect);

    if (m_app_style == GLApp2D) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        double width = rect.right/2.0;
        double height = rect.bottom/2.0;

        glOrtho(-width, width, height, -height, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    } else if (m_app_style == GLApp3D) {
        glViewport(0, 0,(GLsizei)rect.right,(GLsizei)rect.bottom);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1.0, 1.0, -1.0, 1.0, -20, 20.0);
        glMatrixMode(GL_MODELVIEW);
    }
	
	return GL_NO_ERROR == glGetError();
}

void GLEnvironment::WinSizeChanged(int w, int h)
{
    if (m_app_style == GLApp2D) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        double width = w/2.0;
        double height = h/2.0;
        glOrtho(-width, width, height, -height, 0, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glViewport(0, 0, w, h);

    } else if (m_app_style == GLApp3D) {
        glViewport(0, 0, w, h); 
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
        glMatrixMode(GL_MODELVIEW);
    }
}

void GLEnvironment::Exit()
{
	if (m_context) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_context);
		m_context = NULL;
	}

	if (m_dc) {
		::ReleaseDC(m_wnd, m_dc);
		m_dc = NULL;
	}
}

void GLEnvironment::Draw()
{
	SwapBuffers(m_dc);
}

