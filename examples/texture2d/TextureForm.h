#pragma once
#include "GLForm.h"
#include "GLWidget.h"
#include "LnUI/LDragAssist.h"

class TextureForm : public GLForm
{
public:
    TextureForm(HINSTANCE hin);
    ~TextureForm(void);

protected:
    virtual void OnCreate();
    virtual void OnDraw();

    virtual void OnSize(int cx, int cy);
    virtual void OnKeyDown(GLKeyEventArgsPtr key_args);

    virtual void OnMouseDown(GLMouseEventArgsPtr args);
    virtual void OnMouseMove(GLMouseEventArgsPtr args);
    virtual void OnMouseUp(GLMouseEventArgsPtr args);


private:
    GLWidget m_img1;
    GLWidget m_img2;

    ln::LDragAssist m_drag;

};
