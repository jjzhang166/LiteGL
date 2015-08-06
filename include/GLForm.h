#pragma once

#include <Windows.h>
#include <string>
#include <boost/shared_ptr.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "TGBaseType.h"
#include "GLUtility.h"

enum GLMouseButtons
{
    GLMouseButton_None = 0,
    GLMouseButton_Left,
    GLMouseButton_Right,
    GLMouseButton_Middle,
    GLMouseButton_XButton1,
    GLMouseButton_XButton2,
};

class GLMouseEventArgs
{
public:
    GLMouseEventArgs(GLMouseButtons btn, int clicks, int delta, int x, int y, 
        bool is_shift, bool is_ctrl, bool is_alt)
        :
    m_button(btn),
        m_clicks(clicks),
        m_delta(delta),
        m_location(x, y),
        m_is_shift_down(is_shift),
        m_is_ctrl_down(is_ctrl),
        m_is_alt_down(is_alt)
    { }

    bool IsLeft() 
    {
        return m_button == GLMouseButton_Left;   
    }
    bool IsRight()
    {
        return m_button == GLMouseButton_Right;
    }

public:
    //鼠标按钮
    GLMouseButtons m_button;

    //按下并释放鼠标按钮的次数
    int m_clicks;

    //鼠标轮已转动的计数
    int m_delta;

    //鼠标所在的位置
    TG::PointInt m_location;

    bool m_is_shift_down;
    bool m_is_ctrl_down;
    bool m_is_alt_down;
};


class GLKeyEventArgs
{
public:
    GLKeyEventArgs(int vk_code, bool is_shift, bool is_control, bool is_alt)
        :
    m_vk_code(vk_code),
        m_is_shift(is_shift),
        m_is_control(is_control),
        m_is_alt(is_alt)
    { }


public:
    int m_vk_code;

    bool m_is_shift;
    bool m_is_control;
    bool m_is_alt;

    //指示是否处理过此事件
    //true表示跳过控件的默认处理, false表示还将该事件递给默认控件处理程序
    bool m_is_handled;
};

typedef boost::shared_ptr<GLMouseEventArgs> GLMouseEventArgsPtr;
typedef boost::shared_ptr<GLKeyEventArgs> GLKeyEventArgsPtr;

class GLEnvironment;

class GLForm
{
public:
    GLForm(HINSTANCE hin);
    void Show();

    void SetMinSize(int w, int h);
    void SetStartSize(int w, int h);

    void SetAppStyle(GLAppStyle style);

    int Width() const;
    int Height() const;

    void SetTimer(int id, unsigned int elapse);
    void KillTimer(int id);
   

protected:
    void Draw3d();

    virtual void OnDraw();
    virtual void OnCreate();
    virtual void OnClose();

    virtual void OnSize(int cx, int cy);

    virtual void OnTimer(int id);

    virtual void OnKeyDown(GLKeyEventArgsPtr key_args);
    virtual void OnMouseMove(GLMouseEventArgsPtr args);

    virtual void OnMouseDown(GLMouseEventArgsPtr args);
    virtual void OnMouseUp(GLMouseEventArgsPtr args);

    virtual void OnMouseWheel(GLMouseEventArgsPtr args);

private:
    static LRESULT CALLBACK WndProcS(HWND hwnd, UINT message, WPARAM wp, LPARAM lp);
    LRESULT WndProc(UINT message, WPARAM wp, LPARAM lp);
    int RegesterForm();
    void CreateForm();

    void WinClose();

protected:
    HINSTANCE m_instance;
    HWND m_hwnd;
    int m_start_width;
    int m_start_height;

    std::wstring m_class_name;
    std::wstring m_title_text;
    int m_icon;


    bool m_is_shift_down;
    bool m_is_ctrl_down;
    bool m_is_alt_down;

    GLEnvironment *m_gl_env;
    GLAppStyle m_app_style;

};


//int WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd)
void GLAppRun(GLForm *form);