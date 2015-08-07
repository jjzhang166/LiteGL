#pragma once
#include "GLForm.h"
#include "GLCube.h"
#include "LnUI/LDragAssist.h"

class PickForm : public GLForm
{
public:
    PickForm(HINSTANCE hin);
    ~PickForm(void);

    virtual void OnCreate();
    virtual void OnSize(int cx, int cy);
    virtual void OnDraw();

    virtual void OnKeyDown(GLKeyEventArgsPtr key_args);
    virtual void OnMouseDown(GLMouseEventArgsPtr args);
    virtual void OnMouseMove(GLMouseEventArgsPtr args);
    virtual void OnMouseUp(GLMouseEventArgsPtr args);

private:
    float m_rot_x;
    float m_rot_y;
    float m_rot_z;

    float m_look_z;

    ln::LDragAssist m_drag;
    float m_drag_x;
    float m_drag_y;

    GLCube m_cube1;
    GLCube m_cube2;
};
