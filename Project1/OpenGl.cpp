//Tactical_Hacker
#define _CRT_SECURE_NO_WARNINGS

#include <GL\glew.h>
#include <GL\freeglut.h>
//__
#include <ProjManager.h>

#include "Scene2D.h"
#include "OpenGLRender.h"
#include "KeyBoard.h"
#include "Mouse.h"


#include "Condition.h"

#include "ManagerFigure.h"
#include "Selector.h"

#include "CoordTransform.h"

#include "FigureBase.h"
#include "Point3D.h"

#include "Rect2D.h"

#include "C2DRender.h"
//__
#include <stdio.h>

#include <iostream>
#include <vector>
#include <memory>


#include <time.h> // нужен для вызова функции time()

using namespace std;

//Global_VAR
int WINWIDTH = 1000;
int WINHEIGHT = 950;

// Force Redraw timer
#define TIMER 5.6          // 60 frame per second

//Ortho
GLdouble m_OrthoMinX = 0.00;
GLdouble m_OrthoMaxX = 0.00;

GLdouble m_OrthoMinY = 0.00;
GLdouble m_OrthoMaxY = 0.00;

GLdouble m_OrthoMinZ = 0.00;
GLdouble m_OrthoMaxZ = 0.00;

auto pProjManager = std::make_shared<CProjManager>();

auto pOpenGlRender = std::make_shared<COpenGLRender>();
auto pCondition= std::make_shared<CCondition>();
auto p2DRender = std::make_shared<C2DRender>();
auto pFMGManager = std::make_shared<CManagerFigure>();

auto pKeyBoard = std::make_unique<CKeyBoard>();
auto pMouse = std::make_unique<CMouse>();
//END_Global_VAR

void ChangeSize(GLsizei w, GLsizei h)
{     
	//Определение рабочего окна
	auto pCoorTrans = std::make_unique<CCoordTransform>();

	pCoorTrans->ChangeSize((int)w, (int)h, WINWIDTH, WINHEIGHT, m_OrthoMinX, m_OrthoMaxX, m_OrthoMinY, m_OrthoMaxY);

	pCondition->SetWINWIDTH(WINWIDTH);
	pCondition->SetWINHEIGHT(WINHEIGHT);
}

void KeyStroke(unsigned char key, int x, int y) 
{
	pKeyBoard->KeyStroke(key, x, y);
}

void KeyProcess(int key, int x, int y)
{
	pKeyBoard->KeyProcess(key, x, y);
}

void mouseMotion(int x, int y)
{
	bool IsMouseMove = pCondition->GetIsMouseMove();
	pMouse->MouseMotion(x, y, IsMouseMove);// g_IsMouseMove);
	pCondition->SetIsMouseMove(IsMouseMove);
}

void mouseClick(int button, int state, int x, int y) 
{
	bool IsMouseMove = pCondition->GetIsMouseMove();
	pMouse->MouseClick(button, state, x, y, IsMouseMove);//g_IsMouseMove);
	pCondition->SetIsMouseMove(IsMouseMove);
}

void init(void)
{
	pOpenGlRender->Init(WINWIDTH, WINHEIGHT);
}

void recomputeFrame(int value)
{
	glutPostRedisplay();
}

void Draw(void)
{
	pCondition->GetCurGameState();
	p2DRender->Draw(pCondition->GetCurGameState());
}

void render()
{	
	init();
	
	Draw();
	
	glutSwapBuffers();	

	glutTimerFunc(TIMER, recomputeFrame, 1);
}

void MousePassiveMotion(int x, int y)
{
	pMouse->MousePassiveMotion(x, y);
}

int main(int argc, char* argv[]) 
{
	srand(time(NULL));

	m_OrthoMaxX = 50;
	m_OrthoMinX = -50;
	m_OrthoMaxY = 50;
	m_OrthoMinY = -50;
	m_OrthoMaxZ = 1.0;
	m_OrthoMinZ = -1.0;
	
	pCondition->SetCurGameState(StartMenu);
	pCondition->SetIsMouseMove(false);

	std::string CarsFolder = "Cars";
	pCondition->SetCarsFolder(CarsFolder);

	glutInit(&argc, argv);  // Initialize GLUT

	pFMGManager->SetConditions(pCondition);

	p2DRender->SetFigureManager(pFMGManager);
	
	pMouse->SetFigureManager(pFMGManager);
	pMouse->SetScene2D(p2DRender->GetScene2D());

	pOpenGlRender->InitWindowParams(WINWIDTH, WINHEIGHT, 0, 0);

	pProjManager->SetFMGManager(pFMGManager);
	pProjManager->SetConditions(pCondition);
	pProjManager->Set2DRender(p2DRender);
	pProjManager->SetScene(p2DRender->GetScene2D());

	pKeyBoard->SetProjManager(pProjManager);

	glutCreateWindow("TestGL");   // Create the window with the title "Tactical_Hacker,GL"
//--
	
//--
	glutDisplayFunc(render);
	glutReshapeFunc(ChangeSize);

	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);

	glutSpecialFunc(KeyProcess);
	glutKeyboardFunc(KeyStroke);
	glutMainLoop();
//--
	return 0;
}