#pragma once

#include <Windows.h>
#include <GL\gl.h>

struct LGLVertex
{
	// GL_T2F_V3F
	float tu, tv;
	float x, y, z;
};

// This class create a set of vertices's of GL_T2F_V3F type.
// SetAt will update the vertex information of a index.
// DrawVertexBuffer will pass the vertex informations to GPU.
class GLVertexBuffer
{
public:
	GLVertexBuffer(void);
	~GLVertexBuffer(void);
	bool Create(int nCount_i);
    void CreateQuadVertexBuffer();
	void Delete();
	bool SetAt(int index, float x, float y, float z, float u, float v);
	void DrawVertexBuffer(GLenum eDrawPrimitive_i);
    void Rotate(int nRotate_i);

    LGLVertex Get(int nIndex_i) {
        return m_pVertexBuffer[nIndex_i];
    }
	int			m_nCount;
	LGLVertex*	m_pVertexBuffer;
    int m_nRotate;
};
