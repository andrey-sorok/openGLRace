#ifndef __OPENGLRENDER_
#define __OPENGLRENDER_

#include <utility>

class COpenGLRender
{
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