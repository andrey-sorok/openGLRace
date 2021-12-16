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
#include "C2DGenModel.h"
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
	int x1 = static_cast<int>(x);

	for (c = string; *c != '\0'; c++)
	{
		glRasterPos2f((GLfloat)x1, (GLfloat)y);
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

	int NumModels = static_cast<int>(vModels2D.size());

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

			int centerX = static_cast<int>((iGrid[iGridRect].second.x + iGrid[iGridRect].first.x) / 2);
			int centerY = static_cast<int>((iGrid[iGridRect].second.y + iGrid[iGridRect].first.y) / 2);
			
			CPoint2D minXY(iGrid[iGridRect].first.x, iGrid[iGridRect].first.y);
			CPoint2D maxXY(iGrid[iGridRect].second.x, iGrid[iGridRect].second.y);

			CPoint2D p(static_cast<float>(centerX), static_cast<float>(centerY));

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
	int sizeObj2D = static_cast<int>(vRedactSceneObj.size());
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
			bool IsGenerate = pMNGFigure->GetConditions()->GetIsGenerate();
			if (!IsGenerate)
			{
				std::vector<std::shared_ptr<C2DGenModel>> Track1Models = m_pScene2D->GenerateTrack1Models();
				m_pScene2D->SeTrack1Models(Track1Models);
				pMNGFigure->GetConditions()->SetIsGenerate(true);
			}
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
		glColor3f(static_cast<GLfloat>(pColor->R), static_cast<GLfloat>(pColor->G), static_cast<GLfloat>(pColor->B));
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
		glColor3f(static_cast<GLfloat>(pColor->R), static_cast<GLfloat>(pColor->G), static_cast<GLfloat>(pColor->B));
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
		glColor3f(static_cast<GLfloat>(pColor->R), static_cast<GLfloat>(pColor->G), static_cast<GLfloat>(pColor->B));

		float theta = 2.0f * 3.1415926f * float(ii) / float(Segments);//get the current angle 
		float x = static_cast<float>(Radius * cosf(theta));//calculate the x component 
		float y = static_cast<float>(Radius * sinf(theta));//calculate the y component 
		ii++;
		glVertex2f(Center.x, Center.y);//center	
		glVertex2f(x + Center.x, y + Center.y);//first vertex 

		theta = 2.0f * 3.1415926f * float(ii) / float(Segments);//get the current angle 
		x = static_cast<float>(Radius * cosf(theta));//calculate the x component 
		y = static_cast<float>(Radius * sinf(theta));//calculate the y component 

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
	glColor3f(static_cast<GLfloat>(inColor->R), static_cast<GLfloat>(inColor->G), static_cast<GLfloat>(inColor->B));

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

void C2DRender::DrawTrack1Objects()
{
	auto pConditions = pMNGFigure->GetConditions();

	auto TrackModels = m_pScene2D->GetTrack1Models();
	for (auto iModel : TrackModels)
	{
		auto CurPosXY = iModel->GetCurPositionXY();
		auto MinMaxXY = iModel->GetMinMaxModelRect(iModel->GetObjects2D());
		auto wHeight = pConditions->GetWINHEIGHT();

		auto CerbHeight = pConditions->GetCerbHeight();

		if ((((wHeight / 2) + CurPosXY->y + MinMaxXY.first.y) <= CerbHeight)|| (((wHeight / 2) + CurPosXY->y + MinMaxXY.second.y) >= (wHeight - CerbHeight)))//up cerb and bottom cerb
		{
			int dY = iModel->GetdY();
			dY *= -1;
			iModel->SetdY(dY);
		}

		CurPosXY->y += iModel->GetdY();
		iModel->SetCurPositionXY(CPoint2D(CurPosXY->x, CurPosXY->y));
	
		auto Objects = iModel->GetObjects2D();
		for (auto iFigure : Objects)
		{
			glPushMatrix();
			glTranslatef(static_cast<float>((pConditions->GetWINWIDTH() / 2)), static_cast<float>((pConditions->GetWINHEIGHT() / 2) + CurPosXY->y), 0);

			auto pBase = iFigure.get();
			Draw2DOject(pBase);

			glPopMatrix();
		}
	}
}

void C2DRender::DrawTrack1()
{

	auto pCondition = pMNGFigure->GetConditions();

//DrawCarModel
	std::shared_ptr<C2DModel> pCurModel = m_pScene2D->GetCurModel();
	//rectangl around Car
	auto RectLengthXY = pCondition->GetRectForCarInTrack();
	
	auto centerXY = pCurModel->GetCenter();
	auto MinMaxXYRect = pCurModel->GetMinMaxRectXY();

	float lengthModelX = MinMaxXYRect.second.x - MinMaxXYRect.first.x;
	float lengthModelY = MinMaxXYRect.second.y - MinMaxXYRect.first.y;
//__
		
	double oldScaleX = pCurModel->GetScaleX();
	double oldScaleY = pCurModel->GetScaleY();
	
	auto pMinMaxXY = pCurModel->GetMinMaxModelRect(pCurModel->GetObjects2D());
	
	//float lengthModelY = pMinMaxXY.second.x - pMinMaxXY.first.x;
	//float lengthModelX = pMinMaxXY.second.y - pMinMaxXY.first.y;

	//float NewLengthX = RectForModelInTrack.lengthX * scaleX;
	float NewLengthX = lengthModelY * oldScaleX;
	float NewLengthY = lengthModelX * oldScaleY;

	auto pCurPosition = pCurModel->GetCurPositionXY();

	int curX2 = pCurPosition->x + NewLengthX / 2; //pCurPosition->x + (RectForModelInTrack.lengthX / 2);
	int curY2 = pCurPosition->y + NewLengthY / 2; //pCurPosition->y + (RectForModelInTrack.lengthY / 2);

	int curX1 = pCurPosition->x - NewLengthX / 2;
	int curY1 = pCurPosition->y - NewLengthY / 2;

	auto pLine1 = std::make_shared<CLine2D>(CPoint2D(curX1, curY1), CPoint2D(curX2, curY1), CColor3D(255, 0, 0));
	auto pLine2 = std::make_shared<CLine2D>(CPoint2D(curX2, curY1), CPoint2D(curX2, curY2), CColor3D(255, 0, 0));

	auto pLine3 = std::make_shared<CLine2D>(CPoint2D(curX2, curY2), CPoint2D(curX1, curY2), CColor3D(255, 0, 0));
	auto pLine4 = std::make_shared<CLine2D>(CPoint2D(curX1, curY2), CPoint2D(curX1, curY1), CColor3D(255, 0, 0));
	
	Draw2DLine(pLine1.get());
	Draw2DLine(pLine2.get());
	Draw2DLine(pLine3.get());
	Draw2DLine(pLine4.get());

//__

	float scaleX = (RectLengthXY.lengthX / lengthModelX);
	float scaleY = (RectLengthXY.lengthY / lengthModelY);

	pCurModel->SetScaleX(scaleX);
	pCurModel->SetScaleY(scaleY);
	
	CPoint2D* offseXY = pCurModel->GetOffset();

	glPushMatrix();

	glTranslatef(RectLengthXY.lengthX + offseXY->x, (pCondition->GetWINHEIGHT() / 2) + offseXY->y, 0);
	glScalef(scaleX, scaleY, 0);
	glRotatef(+90.00, 0, 0, 1);
	glTranslatef(-centerXY.first, -centerXY.second, 0);

	pCurModel->SetCurPositionXY(CPoint2D(RectLengthXY.lengthX + offseXY->x, (pCondition->GetWINHEIGHT() / 2) + offseXY->y));
	
	std::list<std::shared_ptr<CFigureBase>> Objects2D = pCurModel->GetObjects2D();
	for (auto iObj : Objects2D)
	{	
		Draw2DOject(iObj.get());	
	}

	glPopMatrix();
//End_DrawCarModel

//Cerb
	std::shared_ptr<C2DModel > pCurbModel = m_pScene2D->GetCurb();
	GeneRateCerb(pCurbModel);

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
		glTranslatef(-OffsetXY->x, static_cast<float>(height - 25), 0);
		
		Draw2DOject(pBase);

		glPopMatrix();

	}
//end_Cerb

//Game_Objects
	DrawTrack1Objects();
//End_Game_Objects

	int CurLoopTrack1 = pCondition->GetCurLoopDrawTrack1();
	CurLoopTrack1++;
	pCondition->SetCurLoopDrawTrack1(CurLoopTrack1);
}

void C2DRender::GeneRateCerb(std::shared_ptr<C2DModel> InModel)
{
	auto pCondition = pMNGFigure->GetConditions();
	float width = static_cast<float>(pCondition->GetWINWIDTH());
	float NumCurbs = static_cast<float>(pCondition->GetCurbs());

	float offsetX = width / (NumCurbs * NumCurbs * NumCurbs);
	InModel->SetOffset(fHorizontal, offsetX);

	int MaxOffsetX = static_cast<int>(width / NumCurbs);

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
		auto pRect1 = std::make_shared<CRect2D>(CPoint2D(static_cast<float>(curPosX), 0), CPoint2D(static_cast<float>(newPos), static_cast<float>(InCerbHeight)), CColor3D(Color->R, Color->G, Color->B));
		CurObjects2D.emplace_back(pRect1);
		InModel->SetLenghtModel(newPos);
	}
}
