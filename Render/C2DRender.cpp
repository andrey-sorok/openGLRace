#include "C2DRender.h"

#include "FigureBase.h"
#include "Condition.h"

#include "Color3D.h"
#include "Point2D.h"

#include "Rect2D.h"
#include "Triangle2D.h"
#include "Cycle.h"
#include "Line2D.h"

#include "Scene2D.h"

#include <gl\freeglut.h>

#include <math.h>
#include <memory>
#include <vector>


void C2DRender::DrawCurrenFigure(EFigure InCurFigure, CColor3D InColor)
{
	switch(InCurFigure)
	{
		case 1:
		{
			/*auto InLine = dynamic_cast<CLine2D*>(InCurFigure);
			Draw2DLine(InLine);*/
			break;
		}
		case 2: //Triangle
		{
			auto pNewTriangle = new CTriangle2D(50, 425, InColor);
			DrawTriangle2D(pNewTriangle);
			break;
		}
		case 3://Rectangle
		{
			auto pNewRect = new CRect2D(CPoint2D(20, 415), CPoint2D(80, 435), InColor);
			DrawRect2D(pNewRect);
			break;
		}
		case 4://Cycle
		{
			auto pNewCycle = new CCycle(CPoint2D(50, 425), InColor);
			DrawCircle(pNewCycle);
			break;
		}
		default:
		{
			break;
		}
	}
}

void C2DRender::renderSpacedBitmapString(float x, float y, int spacing, void * font, char * string)
{
	char *c;
	int x1 = x;

	for (c = string; *c != '\0'; c++)
	{
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c) + spacing;
	}
}

C2DRender::C2DRender()
{
	m_pScene2D = std::make_shared<CScene2D>();
}

C2DRender::~C2DRender()
{
}

void C2DRender::SetFigureManager(std::shared_ptr<CManagerFigure> InMNGFigure)
{
	pMNGFigure.reset(InMNGFigure.get());
}

void C2DRender::Draw(GameState InGameState)
{

	switch (InGameState)
	{
		case BeginLoading:
		{
			break;
		};

		case StartMenu:
		{
			DrawStartMenu();
			break;
		};

		case Redact:
		{
			DrawRedactComponents();
			break;
		};

		case Game:
		{
			break;
		};

		default:
			break;
	}
}

void C2DRender::DrawRedactComponents()
{

	std::vector<std::shared_ptr<CFigureBase>>  vRedactSceneObj = m_pScene2D->GetDrawRedactObjCondition();
	int sizeObj2D = vRedactSceneObj.size();
	for (int iObj = 0; iObj < sizeObj2D; ++iObj)
	{
		auto pFBase = vRedactSceneObj[iObj].get();
		Draw2DOject(pFBase);
	}

	renderSpacedBitmapString(25, 465, 10, GLUT_BITMAP_TIMES_ROMAN_10, "Save");
	renderSpacedBitmapString(30, 476, 10, GLUT_BITMAP_TIMES_ROMAN_10, "and");
	renderSpacedBitmapString(25, 490, 10, GLUT_BITMAP_TIMES_ROMAN_10, "Exit");
	
	//Cur Figure
	auto pCoditions = pMNGFigure->GetConditions();
	EFigure CurFigure = pCoditions->GetCurFigure();
	if (CurFigure != fNone)
	{
		DrawCurrenFigure(CurFigure, pCoditions->GetCurColor());
	}

	std::vector<CFigureBase*>& vecObjects2D = pMNGFigure->GetObjects();
	sizeObj2D = pMNGFigure->GetObjecs2DSize();
	for (int iObj = 0; iObj < sizeObj2D; ++iObj)
	{
		auto pFBase = vecObjects2D[iObj];
		Draw2DOject(pFBase);
	}

	glutSwapBuffers();
}

void C2DRender::DrawStartMenu()
{
	std::vector<std::shared_ptr<CFigureBase>>  vStartMenuObj = m_pScene2D->GetDrawStartMenuObjCondition();
	for (auto iMenu : vStartMenuObj) 
	{
		Draw2DOject(iMenu.get());
	}

	glColor3f(0,0,255);
	renderSpacedBitmapString(800, 126, 10, GLUT_BITMAP_TIMES_ROMAN_24, "START");
	
	renderSpacedBitmapString(750, 375, 10, GLUT_BITMAP_TIMES_ROMAN_24, "Choice Car");

	renderSpacedBitmapString(750, 675, 10, GLUT_BITMAP_TIMES_ROMAN_24, "Create Car");

	glutSwapBuffers();
}

void C2DRender::Draw2DOject(CFigureBase * pInFigure)
{
	switch (pInFigure->GetType())
	{
	case 1:
	{
		auto InLine = dynamic_cast<CLine2D*>(pInFigure);
		Draw2DLine(InLine);
		break;
	}
	case 2: //Triangle
	{
		auto InTriangle = dynamic_cast<CTriangle2D*>(pInFigure);
		DrawTriangle2D(InTriangle);
		break;
	}
	case 3://Rectangle
	{
		auto InRect = dynamic_cast<CRect2D*>(pInFigure);
		DrawRect2D(InRect);
		break;
	}
	case 4://Cycle
	{
		auto InCycle = dynamic_cast<CCycle*>(pInFigure);
		DrawCircle(InCycle);
		break;
	}
	default:
	{
		break;
	}

	}
}

void C2DRender::Draw2DLine(CLine2D * pInFigure)
{
	std::list<CPoint2D*> lstPoints = pInFigure->GetPoints();
	CColor3D* pColor = pInFigure->GetColor();
	
	CPoint2D* p1 = lstPoints.front();
	lstPoints.pop_front();
	CPoint2D* p2 = lstPoints.front();
	lstPoints.pop_front();

	glBegin(GL_LINES);
	{
		glColor3f(pColor->R, pColor->G, pColor->B);
		glVertex3f(p1->x, p1->y, 0.0);
		glVertex3f(p2->x, p2->y, 0.0);
	}
	glEnd();
}

void C2DRender::Circle(CColor3D * inColor, float cx, float cy, float r, int num_segments)
{
	DrawCircle(inColor, cx, cy, r, num_segments);
}

void C2DRender::DrawRect2D(CRect2D* inRect)
{
	std::list<CPoint2D*> pPoints = inRect->GetPoints();
	CPoint2D* p1 = pPoints.front();
	pPoints.pop_front();
	CPoint2D* p2 = pPoints.front();
	pPoints.pop_front();
	CPoint2D* p3 = pPoints.front();
	pPoints.pop_front();
	CPoint2D* p4 = pPoints.front();;
	pPoints.pop_front();

	CColor3D* pColor = inRect->GetColor();
	
	glBegin(GL_POLYGON);
	{
		glColor3f(pColor->R, pColor->G, pColor->B);
		glVertex3f(p1->x, p1->y, 0.0);
		glVertex3f(p2->x, p2->y, 0.0);
		glVertex3f(p3->x, p3->y, 0.0);
		glVertex3f(p4->x, p4->y, 0.0);
	}
	glEnd();
	
}

void C2DRender::DrawTriangle2D(CTriangle2D * inTriangle)
{
	std::list<CPoint2D*> pPoints = inTriangle->GetPoints();
	CPoint2D* p1 = pPoints.front();
	pPoints.pop_front();
	CPoint2D* p2 = pPoints.front();
	pPoints.pop_front();
	CPoint2D* p3 = pPoints.front();
	pPoints.pop_front();

	CColor3D* pColor = inTriangle->GetColor();
	glBegin(GL_TRIANGLES);
	{
		glColor3f((GLfloat)pColor->R, (GLfloat)pColor->G, (GLfloat)pColor->B);
		glVertex3f(p1->x, p1->y, 0.0);
		glVertex3f(p2->x, p2->y, 0.0);
		glVertex3f(p3->x, p3->y, 0.0);
	}
	glEnd();

}

void C2DRender::DrawCircle(CCycle * inCycle)
{

	CColor3D* pColor = inCycle->GetColor();
	CPoint2D Center = inCycle->GetCenter();
	int Segments = inCycle->GetNumSegments();
	double Radius = inCycle->GetRadius();
	glBegin(GL_TRIANGLE_STRIP);

	for (int ii = 0; ii < Segments+1; ++ii)
	{
		glColor3f(pColor->R, pColor->G, pColor->B);

		float theta = 2.0f * 3.1415926f * float(ii) / float(Segments);//get the current angle 
		float x = Radius * cosf(theta);//calculate the x component 
		float y = Radius * sinf(theta);//calculate the y component 
		ii++;
		glVertex2f(Center.x, Center.y);//center	
		glVertex2f(x + Center.x, y + Center.y);//first vertex 

		theta = 2.0f * 3.1415926f * float(ii) / float(Segments);//get the current angle 
		x = Radius * cosf(theta);//calculate the x component 
		y = Radius * sinf(theta);//calculate the y component 

		glVertex2f(x + Center.x, y + Center.y);//second vertex 
	}
	glEnd();
}

void C2DRender::DrawAxes(CLine2D* inAbciss, CLine2D* inOrdinate)
{
	glLineWidth(2);

	std::list<CPoint2D*> pPoints = inAbciss->GetPoints();
	CPoint2D* p1 = pPoints.front();
	pPoints.pop_front();
	CPoint2D* p2 = pPoints.front();
	
	CColor3D* pColor = inAbciss->GetColor();
	glBegin(GL_LINES);
	{	
		glColor3f((GLfloat)pColor->R, (GLfloat)pColor->G, (GLfloat)pColor->B);
		glVertex3f(p1->x, p1->y, 0.0);
		glVertex3f(p2->x, p2->y, 0.0);
	}
	glEnd();

	pPoints.clear();
	pPoints = inOrdinate->GetPoints();
	p1 = pPoints.front();
	pPoints.pop_front();
	p2 = pPoints.front();

	pColor = inOrdinate->GetColor();
	glBegin(GL_LINES);
	{
		glColor3f((GLfloat)pColor->R, (GLfloat)pColor->G, (GLfloat)pColor->B);
		glVertex3f(p1->x, p1->y, 0.0);
		glVertex3f(p2->x, p2->y, 0.0);
	}
	glEnd();
}

void C2DRender::DrawCircle(CColor3D * inColor, float cx, float cy, float r, int num_segments)
{
	glColor3f(inColor->R, inColor->G, inColor->B);

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) 
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x +cx, y + cy);//output vertex 
	}
	glEnd();
}