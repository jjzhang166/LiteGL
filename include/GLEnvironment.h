#pragma once

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GLUtility.h"

class GLEnvironment
{
public:
	GLEnvironment(void);
	~GLEnvironment(void);

	bool InitGL(HWND wnd);
    void WinSizeChanged(int w, int h);

	void Exit();
	void Draw();


public:
	HGLRC m_context;
	HDC m_dc;
	HWND m_wnd;

    GLAppStyle m_app_style;
};
