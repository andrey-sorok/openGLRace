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
#include <tuple>


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
			DrawMoveTrack1(fOne);
			break;
		};

		default:
			break;
	}
}

void C2DRender::DrawExistingModels()
{
	std::vector<std::vector<std::shared_ptr<CFigureBase>>> vCarsModels = m_pScene2D->GetCarModels();

	std::shared_ptr<CScene2D> pScene2D = GetScene2D();

	//vector of all models
	std::vector<std::shared_ptr<C2DModel>> vModels2D = m_pScene2D->GetModels();

	int NumModels = vModels2D.size();

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

	/*std::vector<CPoint2D> vCentersGrids;
	for (auto iGrid : vPointGrid)
	{
		for (int iGridRect = 0; iGridRect < iGrid.size(); ++iGridRect)
		{
			
			int centerX = (iGrid[iGridRect].second.x + iGrid[iGridRect].first.x) /2;
			int centerY = (iGrid[iGridRect].second.y + iGrid[iGridRect].first.y) /2;

			CPoint2D p(centerX, centerY);
			vCentersGrids.push_back(p);
		}
	}*/

	std::vector<std::tuple<CPoint2D, CPoint2D, CPoint2D>> vCentersGrids;// 1 -center, 2 - Grid minXY, 3 -Grid maxXY
	for (auto iGrid : vPointGrid)
	{
		for (int iGridRect = 0; iGridRect < iGrid.size(); ++iGridRect)
		{

			int centerX = (iGrid[iGridRect].second.x + iGrid[iGridRect].first.x) / 2;
			int centerY = (iGrid[iGridRect].second.y + iGrid[iGridRect].first.y) / 2;
			
			CPoint2D minXY(iGrid[iGridRect].first.x, iGrid[iGridRect].first.y);
			CPoint2D maxXY(iGrid[iGridRect].second.x, iGrid[iGridRect].second.y);

			CPoint2D p(centerX, centerY);

			auto t = std::make_tuple(p, minXY, maxXY);
			vCentersGrids.push_back(t);
		}
	}

	CPoint2D center, minXY, maxXY;
	int first = 0;
	auto Tup = std::tie(center, minXY, maxXY) = vCentersGrids[first];
	float lengthX = maxXY.x - minXY.x;
	float lengthY = maxXY.y - minXY.y;

	for ( int iModel = 0; iModel < NumModels; ++iModel )
	{
		C2DModel* CurModel = vModels2D[iModel].get();
		std::list<std::shared_ptr<CFigureBase>> lstModelObjects = CurModel->GetObjects2D();
		auto modelCenter = CurModel->GetCenter();
		
		auto Tup = std::tie(center, minXY, maxXY) = vCentersGrids[iModel];
		auto MinMaxXYRect = CurModel->GetMinMaxRectXY();

		float lengthModelX = MinMaxXYRect.second.x - MinMaxXYRect.first.x;
		float lengthModelY = MinMaxXYRect.second.y - MinMaxXYRect.first.y;

		float scaleX = (lengthX / lengthModelX);
		float scaleY = (lengthY / lengthModelY);
		
		glPushMatrix();
				
		glTranslatef( center.x, center.y, 0 );

		glScalef(scaleX/2, scaleY/2, 0);

		glRotatef(+90.00, 0, 0, 1);
		glTranslatef(-modelCenter.first, -modelCenter.second, 0);


		for (auto iFigure : lstModelObjects)
		{	
			auto pFBase = iFigure.get();
			Draw2DOject(pFBase);		
		}

		glPopMatrix();
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

	renderSpacedBitmapString(25, 525, 10, GLUT_BITMAP_TIMES_ROMAN_10, "Exit");
	
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

void C2DRender::DrawMoveTrack1(TrackState InState)
{
	switch (InState)
	{
		case fNone: //0
		{
			break;
		}
		
		case fOne: //0
		{
			DrawTrack1();

			break;
		}
		
		case fTwo: //0
		{
			break;
		}
		
		case fThree: //0
		{
			break;
		}
	
		default:
		{
			break;
		}
	}

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

void C2DRender::KeyReDrowTrack(EDirect InDirec, int d)
{
	switch (InDirec)
	{

		/*case fHorizontal:
		{
			auto pCondition = pMNGFigure->GetConditions();
			std::shared_ptr<C2DModel> pCurModel = m_pScene2D->GetCurModel();
			std::list<std::shared_ptr<CFigureBase>> Objects2D = pCurModel->GetObjects2D();

			glPushMatrix();

			glTranslatef(100, 0, 0);

			for (auto iObj : Objects2D)
			{
				Draw2DOject(iObj.get());
			}

			glPopMatrix();
			
			break;
		}
	
		case fVertical:
		{


			break;
		}
	
		default:
			break;*/
	}
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

void C2DRender::DrawTrack1()
{

	auto pCondition = pMNGFigure->GetConditions();
	std::shared_ptr<C2DModel> pCurModel = m_pScene2D->GetCurModel();

	std::list<std::shared_ptr<CFigureBase>> Objects2D = pCurModel->GetObjects2D();
	
	float lengthX = 100;
	float lengthY = 100;
	
	CPoint2D BeginXY(lengthX, pCondition->GetWINHEIGHT() / 2);

	auto centerXY = pCurModel->GetCenter();
	auto MinMaxXYRect = pCurModel->GetMinMaxRectXY();

	float lengthModelX = MinMaxXYRect.second.x - MinMaxXYRect.first.x;
	float lengthModelY = MinMaxXYRect.second.y - MinMaxXYRect.first.y;

	float scaleX = (lengthX / lengthModelX);
	float scaleY = (lengthY / lengthModelY);

	pCurModel->SetScaleX(scaleX);
	pCurModel->SetScaleY(scaleY);
	
	CPoint2D* offseXY = pCurModel->GetOffset();

	glPushMatrix();

	glTranslatef(lengthX + offseXY->x, (pCondition->GetWINHEIGHT() / 2) + offseXY->y, 0);
	glScalef(scaleX, scaleY, 0);
	glRotatef(+90.00, 0, 0, 1);
	glTranslatef(-centerXY.first, -centerXY.second, 0);

	pCurModel->SetCurPositionXY(CPoint2D(lengthX + offseXY->x, (pCondition->GetWINHEIGHT() / 2) + offseXY->y));

	for (auto iObj : Objects2D)
	{	
		Draw2DOject(iObj.get());	
	}

	glPopMatrix();

//Cerb
	std::shared_ptr<C2DModel > pCurbModel = m_pScene2D->GetCurb();
	GeneRateCerb(pCurbModel);
//end_Cerb

	CPoint2D* OffsetXY = pCurbModel->GetOffset();
	int height = pCondition->GetWINHEIGHT();
	std::list<std::shared_ptr<CFigureBase>> lstCurbModelObjects = pCurbModel->GetObjects2D();
	for (auto iFigure : lstCurbModelObjects)
	{	
		glPushMatrix();
		glTranslatef( -OffsetXY->x, 0, 0);
		auto pBase = iFigure.get();
		Draw2DOject(pBase);
		
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-OffsetXY->x, height - 25, 0);
		
		Draw2DOject(pBase);

		glPopMatrix();

	}

	int CurLoopTrack1 = pCondition->GetCurLoopDrawTrack1();
	CurLoopTrack1++;
	pCondition->SetCurLoopDrawTrack1(CurLoopTrack1);
}

void C2DRender::GeneRateCerb(std::shared_ptr<C2DModel> InModel)
{
	auto pCondition = pMNGFigure->GetConditions();
	float width = pCondition->GetWINWIDTH();
	float NumCurbs = pCondition->GetCurbs();

	float offsetX = width / (NumCurbs * NumCurbs * NumCurbs);
	InModel->SetOffset(fHorizontal, offsetX);

	int MaxOffsetX = width / NumCurbs;

	CPoint2D* OffsetXY = InModel->GetOffset();

	int CurLoopTrack1 = pCondition->GetCurLoopDrawTrack1();
	int MinLoop = 24;
	int MaxLoop = 100;
	if (CurLoopTrack1 == MinLoop)
	{
		int tmpLoop = InModel->GetTimeSet1();
		tmpLoop += CurLoopTrack1;
		InModel->SetTimeSet1(tmpLoop);

		int InCerbHeight = pCondition->GetCerbHeight();
		pCondition->SetCurLoopDrawTrack1(0);
		std::list<std::shared_ptr<CFigureBase>>& CurObjects2D = InModel->GetObjects2D();

		int dif = tmpLoop / MinLoop;
		if (dif == 3)
		{
			CurObjects2D.pop_front();//list front position list clear 
			InModel->SetTimeSet1(0);
		}

		auto pRect = CurObjects2D.back();
		auto pColor = pRect->GetColor();

		CColor3D* Color = new CColor3D(0, 0, 0);
		if ((pColor->R == Color->R) && (pColor->G == Color->G) && (pColor->B == Color->B))
		{
			Color->R = 255;
			Color->G = 255;
			Color->B = 255;
		}

		int curPosX = InModel->GetLenghtModel();
		int newPos = curPosX + MaxOffsetX;
		auto pRect1 = std::make_shared<CRect2D>(CPoint2D(curPosX, 0), CPoint2D(newPos, InCerbHeight), CColor3D(Color->R, Color->G, Color->B));
		CurObjects2D.emplace_back(pRect1);
		InModel->SetLenghtModel(newPos);
	}
}
