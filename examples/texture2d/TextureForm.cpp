#define GLEW_STATIC
#include "GL/glew.h"
#include "TextureForm.h"
#include "GLUtility.h"

TextureForm::TextureForm(HINSTANCE hin)
: GLForm(hin)
{
}

TextureForm::~TextureForm(void)
{
}

char *textFileRead(char *fn)
{
	FILE *fp;
	char *content = NULL;
	int count=0;

	if (fn != NULL)
	{
		fp = fopen(fn, "rt");
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0)
			{
				content = new char[sizeof(char)*(count+1)];
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

void AddShaderPrograme(void)
{
    GLuint VShader;			// ¶¥µãshader
    GLuint FShader;			// Æ¬¶Ïshader
    GLuint ShaderPrograme;	// shader³ÌÐò
    char* VShaderCode;		// ¶¥µãshader´úÂë
    char* FShaderCode;      // Æ¬¶Ïshader´úÂë

    __glewCreateShader;
    VShader = glCreateShader(GL_VERTEX_SHADER);
    FShader = glCreateShader(GL_FRAGMENT_SHADER);

    VShaderCode = textFileRead("V.shd");
    FShaderCode = textFileRead("F.shd");
    glShaderSource(VShader, 1, (const char**)&VShaderCode, NULL);
    glShaderSource(FShader, 1, (const char**)&FShaderCode, NULL);
    delete VShaderCode;
    delete FShaderCode;

    glCompileShader(VShader);
    //printInfoLog(1, VShader);
    GLint vertCompiled;
    glGetShaderiv(VShader, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1)
    {
        //Form1->Memo1->Lines->Add("");
        printf("¶¥µãShader±àÒë´íÎó");
    }

    glCompileShader(FShader);
    //printInfoLog(2, FShader);
    GLint fragCompiled;
    glGetShaderiv(VShader, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1)
    {
        //Form1->Memo1->Lines->Add("");
        printf("Æ¬ÔªShader±àÒë´íÎó");
    }

    ShaderPrograme = glCreateProgram();
    glAttachShader(ShaderPrograme, VShader);
    glAttachShader(ShaderPrograme, FShader);

    glLinkProgram(ShaderPrograme);
    //printInfoLog(3, ShaderPrograme);
    GLint progLinked;
    glGetProgramiv(ShaderPrograme, GL_LINK_STATUS, &progLinked);
    if(progLinked != 1)
    {
        //Form1->Memo1->Lines->Add("");
        printf("Á´½ÓÆ÷Á´½Ó´íÎó");
    }

    glUseProgram(ShaderPrograme);

    // ´«µÝShader±äÁ¿
    glUniform1i(glGetUniformLocation(ShaderPrograme, "DataTexture"), 0);
    float iOffset[9] = {-1.0, -1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
    glUniformMatrix3fv(glGetUniformLocation(ShaderPrograme, "iOffset"), 1, false, iOffset);
    float jOffset[9] = {-1.0, 0.0, 1.0, -1.0, 0.0, 1.0, -1.0, 0.0, 1.0};
    glUniformMatrix3fv(glGetUniformLocation(ShaderPrograme, "jOffset"), 1, false, jOffset);
    float Coff[9] = {-1.0, -1.0, -1.0, -1.0, 8.0, -1.0, -1.0, -1.0, -1.0};
    glUniformMatrix3fv(glGetUniformLocation(ShaderPrograme, "Coff"), 1, false, Coff);
} 

void TextureForm::OnCreate()
{
    //printf("before: %d \n", __glewCreateShader);
    GLenum err = glewInit();
    printf("after: %d \n", __glewCreateShader);
    AddShaderPrograme();


    {
        int width, height;
        unsigned char *data;
        GLLoadImage(L"D:\\sh.png", &width, &height, data);
        m_img1.Init(width, height, data);
        delete data;
    }
    {
        int width, height;
        unsigned char *data;
        GLLoadImage(L"D:\\aiqt.jpg", &width, &height, data);
        m_img2.Init(width, height, data);
        delete data;
    }

}

void TextureForm::OnDraw()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);

    m_img1.Draw();
    m_img2.Draw();
}

void TextureForm::OnSize(int w, int h)
{
    m_img1.WinSize(w, h);
    m_img2.WinSize(w, h);

    m_img2.SetPos(w-m_img2.Width(), h-m_img2.Height());
    //m_img1.SetPos((w-m_img1.Width())/2, (h-m_img1.Height())/2);
    //m_img1.RefreshBuffer(offx, offy);

    printf("OnSize: %d, %d\n", w, h);
}

void TextureForm::OnKeyDown(GLKeyEventArgsPtr key_args)
{
    int left = m_img1.Left();
    int top = m_img1.Top();
    switch(key_args->m_vk_code) {
        case VK_LEFT:
            m_img1.SetPos(left-1, top);
            break;

        case VK_RIGHT:
            m_img1.SetPos(left+1, top);
            break;

        case VK_UP:
            m_img1.SetPos(left, top-1);
            break;

        case VK_DOWN:
            m_img1.SetPos(left, top+1);
            break;
    }
    Repaint();
   
}

void TextureForm::OnMouseDown(GLMouseEventArgsPtr args)
{

    m_drag.SetStartPoint(m_img1.Left(), m_img1.Top());
    m_drag.MouseDown(args->m_location);
}

void TextureForm::OnMouseMove(GLMouseEventArgsPtr args)
{
    if (m_drag.IsMouseDown()) {
        ln::PointInt p = m_drag.MouseMove(args->m_location);
        m_img1.SetPos(p.m_x, p.m_y);
        Repaint();
    }
}

void TextureForm::OnMouseUp(GLMouseEventArgsPtr args)
{

    m_drag.MouseUp();
}
