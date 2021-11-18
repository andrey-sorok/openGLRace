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

#include "Condition.h"
#include "BinFile.h"

//__
#include "C2DModel.h"
//__

#include <gl\freeglut.h>

#include <math.h>
#include <memory>


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

		case Choice:
		{
			DrawExistingModels();
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

void C2DRender::DrawExistingModels()
{
	std::vector<std::vector<std::shared_ptr<CFigureBase>>> vCarsModels = m_pScene2D->GetCarModels();

	int NumModels = vCarsModels.size();

	std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> vPointGrid = pMNGFigure->GetConditions()->GetOutModelsGreed();

	for (int irow = 0; irow < vPointGrid.size(); ++irow)
	{
		for (int icol = 0; icol < vPointGrid[irow].size(); ++icol)
		{
			auto pRect = std::make_unique<CRect2D>();
			
			auto P2P4 = pRect->GetP2P4(vPointGrid[irow][icol].first, vPointGrid[irow][icol].second);
			//auto pLine1 = std::make_shared<CLine2D>(vPointGrid[irow][icol].first, P2P4.first, CColor3D(0, 255, 0));
			//Draw2DOject(dynamic_cast<CFigureBase*>(pLine1.get()));

			auto pLine2 = std::make_shared<CLine2D>(P2P4.first, vPointGrid[irow][icol].second, CColor3D(0, 255, 0));
			Draw2DOject(dynamic_cast<CFigureBase*>(pLine2.get()));

			auto pLine3 = std::make_shared<CLine2D>(vPointGrid[irow][icol].second, P2P4.second, CColor3D(0, 255, 0));
			Draw2DOject(dynamic_cast<CFigureBase*>(pLine3.get()));

			//auto pLine4 = std::make_shared<CLine2D>(P2P4.second, vPointGrid[irow][icol].first, CColor3D(0, 255, 0));
			//Draw2DOject(dynamic_cast<CFigureBase*>(pLine4.get()));
		}
	}

	/*std::vector<std::shared_ptr<CFigureBase>> vFirstModel = vCarsModels[0];
	std::vector<std::shared_ptr<CFigureBase>> tmpVec;
	tmpVec.push_back(vFirstModel[1]);

	auto pC2DModel1 = std::make_shared<C2DModel>(vFirstModel);*/
	//std::list<std::shared_ptr<CFigureBase>> lstFigure =  pC2DModel1->GetObjects2D();
	//auto Pair = pC2DModel1->GetVertexArr(lstFigure.front());
	
	/*std::list<std::shared_ptr<CFigureBase>> lstFigure;
	lstFigure.push_back(vFirstModel[1]);
	lstFigure.push_back(vFirstModel[2]);
	
	auto Pair = pC2DModel1->GetAllVrtAndColor(lstFigure);*/
	//auto pModel = m_pScene2D->GetModel();

	//std::list <std::shared_ptr<C2DModel>> pM;
	//pM.emplace_back(pModel[0]);

	/*int size = 0;
	auto Pair = pModel[0]->GetAllVrtAndColor(pModel[0]->GetObjects2D(), size);
	
	
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, Pair.first);
	glColorPointer(3, GL_FLOAT, 0, Pair.second);*/
	
	//glRotatef(-0.05, 0, 0, 100);
	//glTranslatef(-0.5, 0, 0);

	//glScalef(0.005, 00, 0);

	//glDrawArrays(GL_POLYGON, 0, size);
	//glTranslatef(-60, 0, 0);
	//glRotatef(45, 1, 0, 0);

	/*glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();*/

	for ( int iModel = 0; iModel < NumModels; ++iModel )
	{
		
		for (int iFigure = 0; iFigure < vCarsModels[iModel].size(); ++iFigure)
		{
			auto pFBase = vCarsModels[iModel][iFigure].get();

			Draw2DOject(pFBase);
		}
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
	case 1: //Line
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
	case 3: //Rectangle
	{
		auto InRect = dynamic_cast<CRect2D*>(pInFigure);
		DrawRect2D(InRect);
		break;
	}
	case 4: //Cycle
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