#pragma once

#include <Windows.h>
#include <gl/GL.h>
class GLGeometry
{
public:
    GLGeometry(void);
    ~GLGeometry(void);
};

void GLWireCube(GLdouble dSize);
void GLSolidSphere(GLdouble radius, GLint slices, GLint stacks);
void GLSolidCube(GLdouble dSize);