#define GLEW_STATIC
#include "GL/glew.h"
#include "LnImg/LBitmap.h"
#include "ShaderForm.h"

GLuint VShader;			// 顶点shader
GLuint FShader;			// 片断shader
GLuint ShaderPrograme;	// shader程序
char* VShaderCode;		// 顶点shader代码
char* FShaderCode;      // 片断shader代码

GLuint FBObj;  
GLuint TexSource;		// 封装了原始数据的纹理
GLuint TexDestination;  // 封装了运算结果的纹理

char *textFileRead(char *fn)
{
	FILE *fp;
	char *content = NULL;
	int count=0;

	if (fn != NULL) {
		fp = fopen(fn, "rt");

		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) {
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

	if(vertCompiled != 1) {
		//Form1->Memo1->Lines->Add("顶点Shader编译错误");
	}

	glCompileShader(FShader);
	//printInfoLog(2, FShader);
	GLint fragCompiled;
	glGetShaderiv(VShader, GL_COMPILE_STATUS, &fragCompiled);

	if (fragCompiled != 1) {
		//Form1->Memo1->Lines->Add("片元Shader编译错误");
	}

	ShaderPrograme = glCreateProgram();

	glAttachShader(ShaderPrograme, VShader);
	glAttachShader(ShaderPrograme, FShader);

	glLinkProgram(ShaderPrograme);
	//printInfoLog(3, ShaderPrograme);
	GLint progLinked;
	glGetProgramiv(ShaderPrograme, GL_LINK_STATUS, &progLinked);

	if(progLinked != 1) {
		//Form1->Memo1->Lines->Add("链接器链接错误");
	}

	glUseProgram(ShaderPrograme);

	// 传递Shader变量
	glUniform1i(glGetUniformLocation(ShaderPrograme, "DataTexture"), 0);

    // -1 0 1
    // -1 0 1
    // -1 0 1
	float iOffset[9] = {-1.0, -1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
	glUniformMatrix3fv(glGetUniformLocation(ShaderPrograme, "iOffset"), 1, false, iOffset);
	

    // -1 -1 -1
    //  0  0  0
    //  1  1  1
	float jOffset[9] = {-1.0, 0.0, 1.0, -1.0, 0.0, 1.0, -1.0, 0.0, 1.0};
	glUniformMatrix3fv(glGetUniformLocation(ShaderPrograme, "jOffset"), 1, false, jOffset);

    // -1 -1 -1
    // -1  8 -1
    // -1 -1 -1
	float Coff[9] = {-1.0, -1.0, -1.0, -1.0, 8.0, -1.0, -1.0, -1.0, -1.0};
	glUniformMatrix3fv(glGetUniformLocation(ShaderPrograme, "Coff"), 1, false, Coff);
}

ShaderForm::ShaderForm(HINSTANCE hin)
	:
	GLForm(hin)
{

}

ShaderForm::~ShaderForm(void)
{

}

void ShaderForm::OnCreate()
{
	return;
    GLenum err = glewInit();
    printf("after: %d \n", __glewCreateShader);

    ln::LBitmap bmp;
    //bmp.ReadBmp(L"d:\\512.bmp");
    bmp.ReadJpeg(L"D:\\p.jpg");
    //bmp.Conver8To32();
    int w = bmp.Width();
    int h = bmp.Height();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glViewport(0, 0, w, h);  //这里的gl设置不可缺少

    glNewList(1, GL_COMPILE_AND_EXECUTE);
    {
        glBegin(GL_QUADS);
        {
            glTexCoord2f(0.0, 0.0);
            glVertex2f(0.0, 0.0);
            glTexCoord2f(w, 0.0);
            glVertex2f(1, 0.0);
            glTexCoord2f(w, h);
            glVertex2f(1, 1);
            glTexCoord2f(0.0, h);
            glVertex2f(0.0, 1);
        }
        glEnd();
    }
    glEndList();
	
	//glMemoryBarrierEXT(GL_UNIFORM_BARRIER_BIT_EXT);
	glTextureBarrierNV();

    glGenTextures(1, &TexDestination);
    glBindTexture(GL_TEXTURE_RECTANGLE, TexDestination);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //glTexImage2D(GL_TEXTURE_RECTANGLE,0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glGenFramebuffers(1,&FBObj);
    glBindFramebuffer(GL_FRAMEBUFFER, FBObj);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_RECTANGLE, TexDestination, 0);

	//glMemoryBarrierEXT(GL_UNIFORM_BARRIER_BIT_EXT);
	glTextureBarrierNV();

    glGenTextures(1, &TexSource);
    glBindTexture(GL_TEXTURE_RECTANGLE, TexSource);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    AddShaderPrograme();

	//glMemoryBarrierEXT(GL_UNIFORM_BARRIER_BIT_EXT);
	glTextureBarrierNV();
    //////////////////////////////////////////////////////////////////////////
    
	//glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, w, h, GL_RED, GL_UNSIGNED_BYTE, bmp.Pixel());
    glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, bmp.Pixel());

    glCallList(1);
	//glMemoryBarrierEXT(GL_UNIFORM_BARRIER_BIT_EXT);
	glTextureBarrierNV();
    glFinish();

    unsigned char *re = new unsigned char[w * h * 4];

    //glReadPixels(0, 0, w, h, GL_RED, GL_UNSIGNED_BYTE, re);
    glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, re);


    ln::LBitmap r(w, h, 4, re);
    //r.Conver8To32();
    r.WriteBmp(L"d:\\4.bmp");
}
