#include "OpenGLRender.h"

#include <gl\freeglut.h>

COpenGLRender::COpenGLRender()
{
}

COpenGLRender::~COpenGLRender()
{
}

void COpenGLRender::InitSceneColor(unsigned int inR, unsigned int inG, unsigned int inB)
{
	float fR = inR / 255.0F;
	float fG = inG / 255.0F;
	float fB = inB / 255.0F;

	glClearColor(fR, fG, fB, 0.0);
}

void COpenGLRender::InitWindowParams(const int window_width, const int window_height, const int WinPositionWidth, const int WinPositionHeight)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(WinPositionWidth, WinPositionHeight);
	glutInitWindowSize(window_width, window_height);
	//glutInitWindowPosition(WinPositionWidth, WinPositionHeight);
}

void COpenGLRender::Init(int WINWIDTH, int WINHEIGHT)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.2, 0.5, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, WINWIDTH, WINHEIGHT, 0.0f, 0.0f, 1.0f);
}

std::pair<int, int> COpenGLRender::CenterOnScreen(int inWidth, int inHeight)
{
	auto Pair = std::make_pair(((glutGet(GLUT_SCREEN_WIDTH) - inWidth) / 2), (glutGet(GLUT_SCREEN_HEIGHT) - inHeight) / 2);
	return Pair;
	//center_x = (glutGet(GLUT_SCREEN_WIDTH) - inWidth) / 2;
	//center_y = (glutGet(GLUT_SCREEN_HEIGHT) - inHeight) / 2;
}
