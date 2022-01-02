#ifndef __OPENGLRENDER_
#define __OPENGLRENDER_

#include <utility>
#include <string>

#include <gl\freeglut.h>
//#include <gl\gl.h>		// Заголовочный файл для OpenGL32 библиотеки
//#include <gl\glu.h>		// Заголовочный файл для GLu32 библиотеки

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