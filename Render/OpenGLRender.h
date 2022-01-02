#ifndef __OPENGLRENDER_
#define __OPENGLRENDER_

#include <utility>
#include <string>

#include <gl\freeglut.h>
//#include <gl\gl.h>		// ������������ ���� ��� OpenGL32 ����������
//#include <gl\glu.h>		// ������������ ���� ��� GLu32 ����������

class COpenGLRender
{
protected:
	std::string m_PathToTextures;

	GLuint m_Tex;

public:

	COpenGLRender();
	~COpenGLRender();

	void InitSceneColor(unsigned int inR, unsigned int inG, unsigned int inB);
	void InitWindowParams(const int window_width, const int window_height, const int WinPositionWidth, const int WinPositionHeight);

	void Init(int WINWIDTH, int WINHEIGHT);

	std::pair<int, int> CenterOnScreen(int inWidth, int inHeight);

protected:
};

#endif