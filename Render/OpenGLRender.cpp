#include "OpenGLRender.h"

#include <iostream>
#include <cstdio>
#include <fstream>

COpenGLRender::COpenGLRender()
{
	m_PathToTextures = "Textures";
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


	glEnable(GL_TEXTURE_2D);

	glClearColor(static_cast<GLclampf>(0.0), static_cast<GLclampf>(0.2), static_cast<GLclampf>(0.5), static_cast<GLclampf>(0.00));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, WINWIDTH, WINHEIGHT, 0.0f, 0.0f, 1.0f);
}

std::pair<int, int> COpenGLRender::CenterOnScreen(int inWidth, int inHeight)
{
	auto Pair = std::make_pair(((glutGet(GLUT_SCREEN_WIDTH) - inWidth) / 2), (glutGet(GLUT_SCREEN_HEIGHT) - inHeight) / 2);
	return Pair;
}
