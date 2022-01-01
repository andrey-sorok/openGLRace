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

#include "CycleProperty.h"
#include "TriangleProperty.h"

#include "MyMath.h"

#include "ProjManager.h"

#include <gl\freeglut.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <tuple>

#include <chrono>



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
	auto LMDGetRectPoints = [&](std::shared_ptr<C2DGenModel> InModel)
	{
		eModelType mType = InModel->GetiP();
		switch (mType)
		{
			case mRect:
			{
				auto CurPosXY = InModel->GetCurPositionXY();
				auto MinMaxXY = InModel->GetMinMaxModelRect(InModel->GetObjects2D());

				CPoint2D TrackModelPosXY((CurPosXY->x + pMNGFigure->GetConditions()->GetWINWIDTH()), (CurPosXY->y));

				int dX = static_cast<int>((MinMaxXY.second.x - MinMaxXY.first.x) / 2 + MinMaxXY.second.x / 2);
				int dY = static_cast<int>((MinMaxXY.second.y - MinMaxXY.first.y) / 2 + MinMaxXY.second.y / 2);

				CPoint2D minXY(TrackModelPosXY.x, TrackModelPosXY.y);
				CPoint2D maxXY(TrackModelPosXY.x + dX, TrackModelPosXY.y + dY);

				auto Pair = std::make_pair(minXY, maxXY);
				return Pair;

				break;
			}

			case mTriangle:
			{
				break;
			}

			case mCycle:
			{
				break;
			}

			default:
				break;
		}

		return std::make_pair(CPoint2D(), CPoint2D());
	};


	switch (InState)
	{
		case fNone: //0
		{
			break;
		}
		
		case fOne: //0
		{
			auto pConditions = pMNGFigure->GetConditions();
			bool IsGenerate = pConditions->GetIsGenerate();
			if (!IsGenerate)
			{
				int TrackTime = pConditions->GetCurGameTime();
				int NumInterval = pConditions->GetNumTrackIntervals();
				int OneTimreInterval = pConditions->GetIntervalLength();
				int MaxCurLtrackObjects = pConditions->GetMaxTrackObj();

				auto forple = std::make_tuple(TrackTime, NumInterval, OneTimreInterval, MaxCurLtrackObjects);	

				std::vector<std::shared_ptr<C2DGenModel>> CurTrack1Models = m_pScene2D->GetTrack1Models();
				
				std::vector<std::shared_ptr<C2DGenModel>> Track1Models = m_pScene2D->GenerateTrack1Models(pConditions->GetWINHEIGHT(),
						pConditions->GetWINHEIGHT(), forple);
				
				CurTrack1Models.insert(CurTrack1Models.end(), Track1Models.begin(), Track1Models.end());
				if (CurTrack1Models.size() > MaxCurLtrackObjects)
				{
					CurTrack1Models.resize(MaxCurLtrackObjects);
					CurTrack1Models.shrink_to_fit();
				}

				//If Track1 models intersect - change speed
				for (auto iTrackModel : CurTrack1Models)
				{
					for (auto& jTrackModel : CurTrack1Models)
					{
						if (iTrackModel != jTrackModel)
						{
							auto RectObjPoints1 = LMDGetRectPoints(iTrackModel);
							auto RectObjPoints2 = LMDGetRectPoints(jTrackModel);

							auto pMath = std::make_unique<CMyMath>();
							
							bool IsIntesect = pMath->IsRectIntersection(RectObjPoints1, RectObjPoints2);
							if (!IsIntesect)
							{
								IsIntesect = pMath->IsRectIntersection(RectObjPoints2, RectObjPoints1);
							}

							auto CurPosModel1 = iTrackModel->GetCurPositionXY(); 
							auto CurPosModel2 = jTrackModel->GetCurPositionXY();

							if ((CurPosModel1->x >= 0.00))// && 
							if(CurPosModel2->x >= 0.00)
							{
								if (IsIntesect)
								{
									if ((iTrackModel->GetiP() == mRect) && (jTrackModel->GetiP() == mRect))
									{
										int speedObj1 = iTrackModel->GetProperty()->GetSpeed();
										int speedObj2 = jTrackModel->GetProperty()->GetSpeed();
										if (speedObj1 < speedObj2)
										{
											jTrackModel->GetProperty()->SetSpeed(m_pScene2D->GetMaxTrackObjSpeed());
										}
										else
										{
											iTrackModel->GetProperty()->SetSpeed(m_pScene2D->GetMaxTrackObjSpeed());
										}
									}
									//if ((iTrackModel->GetiP() == mTriangle) && (jTrackModel->GetiP() == mTriangle))
									//{
									//	auto Prop = iTrackModel->GetProperty();
									//	auto pTrianProp1 = dynamic_cast<CTriangleProperty*>(Prop.get());
									//	//pTrianProp1->SetIsUp(false);
							

									//	Prop = jTrackModel->GetProperty();	
									//	auto pTrianProp2 = dynamic_cast<CTriangleProperty*>(Prop.get());
									//	
									//	if (pTrianProp1->GetIsUp() == pTrianProp2->GetIsUp())
									//		pTrianProp1->SetIsUp(!pTrianProp1->GetIsUp());


									//}
									//if ((iTrackModel->GetiP() == mCycle) && (jTrackModel->GetiP() == mCycle))
									//{
									//	auto Prop = iTrackModel->GetProperty();
									//	auto pCycleProp1 = dynamic_cast<CCycleProperty*>(Prop.get());
									//	//pCycleProp1->SetIsRebound(false);

									//	Prop = jTrackModel->GetProperty();
									//	auto pCycleProp2 = dynamic_cast<CCycleProperty*>(Prop.get());
									//	
									//	if (pCycleProp1->GetIsRebound() == pCycleProp2->GetIsRebound())
									//		pCycleProp1->SetIsRebound(!pCycleProp1->GetIsRebound());

									//	//pCycleProp->SetIsRebound(true);
									//}

								}
							}

						}
					}
				}
				
				m_pScene2D->SetTrack1Models(CurTrack1Models);
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
		eModelType mType = iModel->GetiP();
		switch (mType)
		{
			case mRect:
			{
				RectBehaviour(iModel);
				break;
			}

			case mCycle:
			{
				CycleBehaviour(iModel);

				break;
			}

			case mTriangle:
			{
				TrianBehavior(iModel);
				break;
			}

			case mСomposite:
			{
				break;
			}

			default:
				break;

		}
		
		//осчет времени генерации модели
		auto Objects = iModel->GetObjects2D();
		for (auto iFigure : Objects)
		{
			auto CurPosXY = iModel->GetCurPositionXY();

			glPushMatrix();
			glTranslatef(static_cast<float>((pConditions->GetWINWIDTH()) + CurPosXY->x), 
						 static_cast<float>( CurPosXY->y), 0);
			
			auto pBase = iFigure.get();
			Draw2DOject(pBase);

			glPopMatrix();
		}
	}
}

void C2DRender::DrawTrack1()
{
	auto begin = std::chrono::steady_clock::now();
//DrawCarModel
	DrawCarModelTrack1();
////End_DrawCarModel

//Cerb
	std::shared_ptr<C2DModel > pCurbModel = m_pScene2D->GetCurb();
	DrawCerbTracl1(pCurbModel);
//end_Cerb

//Game_Objects
	DrawTrack1Objects();
//End_Game_Objects

//Shoot_Obj
	DrawShootTrack1();
//End_Shoot_Obj

//CheckEncounters
	std::shared_ptr<C2DModel> pCurModel = m_pScene2D->GetCurModel();
	CheckEncounters(pCurModel);
//End_CheckEncounters

//CheckShootEncounters
	CheckShootEncounters();
//End_CheckShootEncounters

//DellObjects_Outh_of_View
	CheckOuthOfViewObjectsTrack1();
//End_DellObjects_Outh_of_View

	auto end = std::chrono::steady_clock::now();

	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

	auto pConditions = pMNGFigure->GetConditions();
	auto curGameTime = pConditions->GetCurGameTime();

	curGameTime -= static_cast<int>(elapsed_ms.count());

	pConditions->SetCurGameTime(curGameTime);
}

void C2DRender::DrawCarModelTrack1()
{
	auto pCondition = pMNGFigure->GetConditions();

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

	float NewLengthX = static_cast<float>(lengthModelY * oldScaleX);
	float NewLengthY = static_cast<float>(lengthModelX * oldScaleY);

	auto pCurPosition = pCurModel->GetCurPositionXY();

	/*int curX2 = pCurPosition->x + NewLengthX / 2;
	int curY2 = pCurPosition->y + NewLengthY / 2;

	int curX1 = pCurPosition->x - NewLengthX / 2;
	int curY1 = pCurPosition->y - NewLengthY / 2;
	
	auto pLine1 = std::make_shared<CLine2D>(CPoint2D(curX1, curY1), CPoint2D(curX2, curY1), CColor3D(255, 0, 0));
	auto pLine2 = std::make_shared<CLine2D>(CPoint2D(curX2, curY1), CPoint2D(curX2, curY2), CColor3D(255, 0, 0));

	auto pLine3 = std::make_shared<CLine2D>(CPoint2D(curX2, curY2), CPoint2D(curX1, curY2), CColor3D(255, 0, 0));
	auto pLine4 = std::make_shared<CLine2D>(CPoint2D(curX1, curY2), CPoint2D(curX1, curY1), CColor3D(255, 0, 0));

	Draw2DLine(pLine1.get());
	Draw2DLine(pLine2.get());
	Draw2DLine(pLine3.get());
	Draw2DLine(pLine4.get());*/

	//__

	float scaleX = (RectLengthXY.lengthX / lengthModelX);
	float scaleY = (RectLengthXY.lengthY / lengthModelY);

	pCurModel->SetScaleX(scaleX);
	pCurModel->SetScaleY(scaleY);

	CPoint2D* offseXY = pCurModel->GetOffset();
	int GameTime = pCondition->GetCurGameTime();

	if (GameTime <= 0)
	{
		float offset = pCondition->GetOffset();		
		pCurModel->SetOffset(fHorizontal, +offset);
	}

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
}

void C2DRender::DrawCerbTracl1(std::shared_ptr<C2DModel> InModel)
{
	auto pCondition = pMNGFigure->GetConditions();

	std::shared_ptr<C2DModel > pCurbModel = m_pScene2D->GetCurb();

	float width = static_cast<float>(pCondition->GetWINWIDTH());
	float NumCurbs = static_cast<float>(pCondition->GetCurbs());

	float offsetX = width / (NumCurbs * NumCurbs * NumCurbs);
	pCurbModel->SetOffset(fHorizontal, offsetX);

	CPoint2D* OffsetXY = pCurbModel->GetOffset();
	int height = pCondition->GetWINHEIGHT();
	std::list<std::shared_ptr<CFigureBase>> lstCurbModelObjects = pCurbModel->GetObjects2D();
	int ind = 0;
	for (auto iFigure : lstCurbModelObjects)
	{
		//UpCerb
		glPushMatrix();
		glTranslatef(-OffsetXY->x, 0, 0);
		auto pBase = iFigure.get();
		Draw2DOject(pBase);

		glPopMatrix();

		//DownCerb
		glPushMatrix();
		glTranslatef(-OffsetXY->x, static_cast<float>(height - 25), 0);

		Draw2DOject(pBase);

		glPopMatrix();

	}
	int lenModel = pCurbModel->GetLenghtModel();
	if (OffsetXY->x >= (lenModel / 2))
	{
		OffsetXY->x = 0.00;
	}
}

void C2DRender::DrawShootTrack1()
{
	auto pConditions = pMNGFigure->GetConditions();
	std::shared_ptr<C2DModel > pCurbModel = m_pScene2D->GetCurModel();

	auto pShotModels = m_pScene2D->GetTtrack1ShootModels();

	for (auto& iModel : pShotModels)
	{
		auto pCurPos = iModel->GetCurPositionXY();
		int maxSpeed = m_pScene2D->GetMaxTrackObjSpeed();
		//осчет времени генерации модели
		auto Objects = iModel->GetObjects2D();
		for (auto iFigure : Objects)
		{
			auto CurPosXY = iModel->GetCurPositionXY();
			CurPosXY->x += maxSpeed*2;
			glPushMatrix();
			glTranslatef(static_cast<float>(CurPosXY->x),
				static_cast<float>(CurPosXY->y), 0);

			auto pBase = iFigure.get();
			Draw2DOject(pBase);

			glPopMatrix();
		}
	}
}

void C2DRender::CheckEncounters(std::shared_ptr<C2DModel> pCurModel)
{
	auto TrackModels = m_pScene2D->GetTrack1Models();

	auto CurPosXY = pCurModel->GetCurPositionXY();
	std::list<int> lstNewRectCoord = pMNGFigure->GetChengedCarRect(pCurModel);

	int x = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();
	int y = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();

	CPoint2D p1(static_cast<float>(x), static_cast<float>(y));

	x = lstNewRectCoord.front();
	lstNewRectCoord.pop_front();
	y = lstNewRectCoord.front();

	CPoint2D p2(static_cast<float>(x), static_cast<float>(y));
	auto PairPointCarMinMax = std::make_pair(p1, p2);
	bool IsIntesect = false;
	for (auto iModel : TrackModels)
	{
		eModelType mType = iModel->GetiP();
		
		switch (mType)
		{
			case mCar:			//0
			{
				break;
			}

			case mСurb:			//1
			{
				break;
			}

			case mRect:			//2
			{
				auto CurPosXY = iModel->GetCurPositionXY();
				auto MinMaxXY = iModel->GetMinMaxModelRect(iModel->GetObjects2D());

				CPoint2D TrackModelPosXY((CurPosXY->x + pMNGFigure->GetConditions()->GetWINWIDTH()), (CurPosXY->y));

				int dX = static_cast<int>((MinMaxXY.second.x - MinMaxXY.first.x) / 2 + MinMaxXY.second.x / 2);
				int dY = static_cast<int>((MinMaxXY.second.y - MinMaxXY.first.y) / 2 + MinMaxXY.second.y / 2);

				CPoint2D minXY(TrackModelPosXY.x, TrackModelPosXY.y);
				CPoint2D maxXY(TrackModelPosXY.x + dX, TrackModelPosXY.y + dY);

				/*auto pLine1 = std::make_shared<CLine2D>(CPoint2D(minXY.x, minXY.y), CPoint2D(maxXY.x, minXY.y), CColor3D(255, 255, 0));
				auto pLine2 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, minXY.y), CPoint2D(maxXY.x, maxXY.y), CColor3D(255, 255, 0));

				auto pLine3 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, maxXY.y), CPoint2D(minXY.x, maxXY.y), CColor3D(255, 255, 0));
				auto pLine4 = std::make_shared<CLine2D>(CPoint2D(minXY.x, maxXY.y), CPoint2D(minXY.x, minXY.y), CColor3D(255, 255, 0));

				Draw2DLine(pLine1.get());
				Draw2DLine(pLine2.get());
				Draw2DLine(pLine3.get());
				Draw2DLine(pLine4.get());*/

				auto TrackModelMinMaxXY = std::make_pair(minXY, maxXY);
				auto pMath = std::make_unique<CMyMath>();

				IsIntesect = pMath->IsRectIntersection(PairPointCarMinMax, TrackModelMinMaxXY);
				
				break;
			}

			case mCycle:		//3
			{
				auto CurPosXY = iModel->GetCurPositionXY();
				auto Obj = iModel->GetObjects2D();
				auto Cucle = dynamic_cast<CCycle*>(Obj.front().get());
				auto radius = Cucle->GetRadius();

				CPoint2D MinXY(static_cast<float>(CurPosXY->x - radius), static_cast<float>(CurPosXY->y - radius));
				CPoint2D MaxXY(static_cast<float>(CurPosXY->x + radius), static_cast<float>(CurPosXY->y + radius));
				CPoint2D TrackModelPosXY(static_cast<float>((CurPosXY->x + pMNGFigure->GetConditions()->GetWINWIDTH())), static_cast<float>((CurPosXY->y)));

				int dX = static_cast<int>(MaxXY.x - MinXY.x);
				int dY = static_cast<int>(MaxXY.y - MinXY.y);

				CPoint2D minXY(TrackModelPosXY.x - dX / 2, TrackModelPosXY.y - dY / 2);
				CPoint2D maxXY(TrackModelPosXY.x + dX / 2, TrackModelPosXY.y + dY / 2);

				/*auto pLine1 = std::make_shared<CLine2D>(CPoint2D(minXY.x, minXY.y), CPoint2D(maxXY.x, minXY.y), CColor3D(255, 255, 0));
				auto pLine2 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, minXY.y), CPoint2D(maxXY.x, maxXY.y), CColor3D(255, 255, 0));

				auto pLine3 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, maxXY.y), CPoint2D(minXY.x, maxXY.y), CColor3D(255, 255, 0));
				auto pLine4 = std::make_shared<CLine2D>(CPoint2D(minXY.x, maxXY.y), CPoint2D(minXY.x, minXY.y), CColor3D(255, 255, 0));

				Draw2DLine(pLine1.get());
				Draw2DLine(pLine2.get());
				Draw2DLine(pLine3.get());
				Draw2DLine(pLine4.get());*/

				auto TrackModelMinMaxXY = std::make_pair(minXY, maxXY);
				auto pMath = std::make_unique<CMyMath>();

				IsIntesect = pMath->IsRectIntersection(PairPointCarMinMax, TrackModelMinMaxXY);

				break;
			}

			case mTriangle:		//4
			{
				auto CurPosXY = iModel->GetCurPositionXY();
				auto MinMaxXY = iModel->GetMinMaxModelRect(iModel->GetObjects2D());

				CPoint2D TrackModelPosXY((CurPosXY->x + pMNGFigure->GetConditions()->GetWINWIDTH()), (CurPosXY->y ));

				int dX = static_cast<int>((MinMaxXY.second.x - MinMaxXY.first.x) / 2);// +MinMaxXY.second.x / 2;
				int dY = static_cast<int>((MinMaxXY.second.y - MinMaxXY.first.y) / 2);// +MinMaxXY.second.y / 2;

				CPoint2D minXY(TrackModelPosXY.x - 2*dX, TrackModelPosXY.y - dY);
				CPoint2D maxXY(TrackModelPosXY.x, TrackModelPosXY.y + dY);

				//auto pLine1 = std::make_shared<CLine2D>(CPoint2D(minXY.x, minXY.y), CPoint2D(maxXY.x, minXY.y), CColor3D(255, 255, 0));
				//auto pLine2 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, minXY.y), CPoint2D(maxXY.x, maxXY.y), CColor3D(255, 255, 0));

				//auto pLine3 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, maxXY.y), CPoint2D(minXY.x, maxXY.y), CColor3D(255, 255, 0));
				//auto pLine4 = std::make_shared<CLine2D>(CPoint2D(minXY.x, maxXY.y), CPoint2D(minXY.x, minXY.y), CColor3D(255, 255, 0));

				//Draw2DLine(pLine1.get());
				//Draw2DLine(pLine2.get());
				//Draw2DLine(pLine3.get());
				//Draw2DLine(pLine4.get());

				auto TrackModelMinMaxXY = std::make_pair(minXY, maxXY);
				auto pMath = std::make_unique<CMyMath>();

				IsIntesect = pMath->IsRectIntersection(PairPointCarMinMax, TrackModelMinMaxXY);

				break;
			}

			case mСomposite:	//5
			{
				break;
			}

			default:
				break;
		}

		if (IsIntesect)
		{
			auto pConditions = pMNGFigure->GetConditions();
			pConditions->SetCurGameTime(pConditions->GetFirstLevelTime());

			ReloadLevel(fOne);
		}


	}

}

void C2DRender::CheckShootEncounters()
{
	auto pTrack1Models = m_pScene2D->GetTrack1Models();
	auto pShootModels = m_pScene2D->GetTtrack1ShootModels();

	for (auto iShoot : pShootModels)
	{
		auto CurPosXY = iShoot->GetCurPositionXY();

		auto MinMAxXY = iShoot->GetMinMaxRectXY();
		int dX = static_cast<int>(MinMAxXY.second.x / 2);
		int dY = static_cast<int>(MinMAxXY.second.y / 2);
		
		CPoint2D p1(CurPosXY->x -dX, CurPosXY->y -dY);
		CPoint2D p2(CurPosXY->x + dX, CurPosXY->y + dY);
		auto PairPointCarMinMax = std::make_pair(p1, p2);


		auto pLine1 = std::make_shared<CLine2D>(CPoint2D(p1.x, p1.y), CPoint2D(p2.x, p1.y), CColor3D(255, 255, 0));
		auto pLine2 = std::make_shared<CLine2D>(CPoint2D(p2.x, p1.y), CPoint2D(p2.x, p2.y), CColor3D(255, 255, 0));

		auto pLine3 = std::make_shared<CLine2D>(CPoint2D(p2.x, p2.y), CPoint2D(p1.x, p2.y), CColor3D(255, 255, 0));
		auto pLine4 = std::make_shared<CLine2D>(CPoint2D(p1.x, p2.y), CPoint2D(p1.x, p1.y), CColor3D(255, 255, 0));

		Draw2DLine(pLine1.get());
		Draw2DLine(pLine2.get());
		Draw2DLine(pLine3.get());
		Draw2DLine(pLine4.get());

		bool IsIntesect = false;
		for (int i = 0; i < pTrack1Models.size(); ++i)
		{
			auto iModel = pTrack1Models[i];
			
			eModelType mType = iModel->GetiP();

			switch (mType)
			{

				case mRect:			//2
				{
					auto CurPosXY = iModel->GetCurPositionXY();
					auto MinMaxXY = iModel->GetMinMaxModelRect(iModel->GetObjects2D());

					CPoint2D TrackModelPosXY((CurPosXY->x + pMNGFigure->GetConditions()->GetWINWIDTH()), (CurPosXY->y));

					int dX = static_cast<int>((MinMaxXY.second.x - MinMaxXY.first.x) / 2 + MinMaxXY.second.x / 2);
					int dY = static_cast<int>((MinMaxXY.second.y - MinMaxXY.first.y) / 2 + MinMaxXY.second.y / 2);

					CPoint2D minXY(TrackModelPosXY.x, TrackModelPosXY.y);
					CPoint2D maxXY(TrackModelPosXY.x + dX, TrackModelPosXY.y + dY);

					/*auto pLine1 = std::make_shared<CLine2D>(CPoint2D(minXY.x, minXY.y), CPoint2D(maxXY.x, minXY.y), CColor3D(255, 255, 0));
					auto pLine2 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, minXY.y), CPoint2D(maxXY.x, maxXY.y), CColor3D(255, 255, 0));

					auto pLine3 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, maxXY.y), CPoint2D(minXY.x, maxXY.y), CColor3D(255, 255, 0));
					auto pLine4 = std::make_shared<CLine2D>(CPoint2D(minXY.x, maxXY.y), CPoint2D(minXY.x, minXY.y), CColor3D(255, 255, 0));

					Draw2DLine(pLine1.get());
					Draw2DLine(pLine2.get());
					Draw2DLine(pLine3.get());
					Draw2DLine(pLine4.get());*/

					auto TrackModelMinMaxXY = std::make_pair(minXY, maxXY);
					auto pMath = std::make_unique<CMyMath>();

					IsIntesect = pMath->IsRectIntersection(PairPointCarMinMax, TrackModelMinMaxXY);
					IsIntesect = pMath->IsRectIntersection(TrackModelMinMaxXY, PairPointCarMinMax);

					break;
				}

				case mCycle:		//3
				{
					auto CurPosXY = iModel->GetCurPositionXY();
					auto Obj = iModel->GetObjects2D();
					auto Cucle = dynamic_cast<CCycle*>(Obj.front().get());
					auto radius = Cucle->GetRadius();

					CPoint2D MinXY(static_cast<float>(CurPosXY->x - radius), static_cast<float>(CurPosXY->y - radius));
					CPoint2D MaxXY(static_cast<float>(CurPosXY->x + radius), static_cast<float>(CurPosXY->y + radius));
					CPoint2D TrackModelPosXY((CurPosXY->x + pMNGFigure->GetConditions()->GetWINWIDTH()), (CurPosXY->y));

					int dX = static_cast<int>(MaxXY.x - MinXY.x);
					int dY = static_cast<int>(MaxXY.y - MinXY.y);

					CPoint2D minXY(TrackModelPosXY.x - dX / 2, TrackModelPosXY.y - dY / 2);
					CPoint2D maxXY(TrackModelPosXY.x + dX / 2, TrackModelPosXY.y + dY / 2);

					/*auto pLine1 = std::make_shared<CLine2D>(CPoint2D(minXY.x, minXY.y), CPoint2D(maxXY.x, minXY.y), CColor3D(255, 255, 0));
					auto pLine2 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, minXY.y), CPoint2D(maxXY.x, maxXY.y), CColor3D(255, 255, 0));

					auto pLine3 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, maxXY.y), CPoint2D(minXY.x, maxXY.y), CColor3D(255, 255, 0));
					auto pLine4 = std::make_shared<CLine2D>(CPoint2D(minXY.x, maxXY.y), CPoint2D(minXY.x, minXY.y), CColor3D(255, 255, 0));

					Draw2DLine(pLine1.get());
					Draw2DLine(pLine2.get());
					Draw2DLine(pLine3.get());
					Draw2DLine(pLine4.get());*/

					auto TrackModelMinMaxXY = std::make_pair(minXY, maxXY);
					auto pMath = std::make_unique<CMyMath>();

					IsIntesect = pMath->IsRectIntersection(PairPointCarMinMax, TrackModelMinMaxXY);
					IsIntesect = pMath->IsRectIntersection(TrackModelMinMaxXY, PairPointCarMinMax);

					break;
				}

				case mTriangle:		//4
				{
					auto CurPosXY = iModel->GetCurPositionXY();
					auto MinMaxXY = iModel->GetMinMaxModelRect(iModel->GetObjects2D());

					CPoint2D TrackModelPosXY((CurPosXY->x + pMNGFigure->GetConditions()->GetWINWIDTH()), (CurPosXY->y));

					int dX = static_cast<int>((MinMaxXY.second.x - MinMaxXY.first.x) / 2);// +MinMaxXY.second.x / 2;
					int dY = static_cast<int>((MinMaxXY.second.y - MinMaxXY.first.y) / 2);// +MinMaxXY.second.y / 2;

					CPoint2D minXY(TrackModelPosXY.x - 2 * dX, TrackModelPosXY.y - dY);
					CPoint2D maxXY(TrackModelPosXY.x, TrackModelPosXY.y + dY);

					/*auto pLine1 = std::make_shared<CLine2D>(CPoint2D(minXY.x, minXY.y), CPoint2D(maxXY.x, minXY.y), CColor3D(255, 255, 0));
					auto pLine2 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, minXY.y), CPoint2D(maxXY.x, maxXY.y), CColor3D(255, 255, 0));

					auto pLine3 = std::make_shared<CLine2D>(CPoint2D(maxXY.x, maxXY.y), CPoint2D(minXY.x, maxXY.y), CColor3D(255, 255, 0));
					auto pLine4 = std::make_shared<CLine2D>(CPoint2D(minXY.x, maxXY.y), CPoint2D(minXY.x, minXY.y), CColor3D(255, 255, 0));

					Draw2DLine(pLine1.get());
					Draw2DLine(pLine2.get());
					Draw2DLine(pLine3.get());
					Draw2DLine(pLine4.get());*/

					auto TrackModelMinMaxXY = std::make_pair(minXY, maxXY);
					auto pMath = std::make_unique<CMyMath>();

					IsIntesect = pMath->IsRectIntersection(PairPointCarMinMax, TrackModelMinMaxXY);
					IsIntesect = pMath->IsRectIntersection(TrackModelMinMaxXY, PairPointCarMinMax);

					break;
				}

				default:
					break;
			}

			if (IsIntesect)
			{
				bool IsUnique = iModel.unique();
				pTrack1Models.erase(pTrack1Models.begin() + i);
				iModel.reset();

				m_pScene2D->SetTrack1Models(pTrack1Models);
			}
		}
	}
}

void C2DRender::CheckOuthOfViewObjectsTrack1()
{
	auto pConditions = pMNGFigure->GetConditions();
	auto TrackModels = m_pScene2D->GetTrack1Models();

	int GameTime = pConditions->GetCurGameTime();

	if (GameTime < 0)
	{
		for (int iModel = 0; iModel < TrackModels.size(); ++iModel)
		{
			auto pModel = TrackModels[iModel];

			bool IsUnique = pModel.unique();
			TrackModels.erase(TrackModels.begin() + iModel);
			pModel.reset();
		}
		m_pScene2D->SetTrack1Models(TrackModels);
	}
	else
	{
		int size = static_cast<int>(TrackModels.size());
		for (int iModel = 0; iModel < TrackModels.size(); ++iModel)
		{
			auto pModel = TrackModels[iModel];

			auto CurPosXY = pModel->GetCurPositionXY();

			int offset = static_cast<int>(pConditions->GetCarOffset());
			if (((pConditions->GetWINWIDTH()) + CurPosXY->x) < -offset)
			{
				bool IsUnique = pModel.unique();
				TrackModels.erase(TrackModels.begin() + iModel);
				pModel.reset();
			}
		}


		if (size > TrackModels.size())
		{
			//bool IsGenerate = false;
			//pConditions->SetIsGenerate(IsGenerate);
			m_pScene2D->SetTrack1Models(TrackModels);
		}
		//if (TrackModels.empty())
		if (pConditions->GetMaxTrackObj() > TrackModels.size())
		{
			bool IsGenerate = false;
			pConditions->SetIsGenerate(IsGenerate);
		}
	}
	//ShootModels
	auto pShootTrackModels = m_pScene2D->GetTtrack1ShootModels();

	int size = static_cast<int>(pShootTrackModels.size());
	for (int iModel = 0; iModel < pShootTrackModels.size(); ++iModel)
	{
		auto pModel = pShootTrackModels[iModel];

		auto CurPosXY = pModel->GetCurPositionXY();

		int offset = static_cast<int>(pConditions->GetCarOffset());
		if (( CurPosXY->x + offset) > pConditions->GetWINWIDTH())
		{
			bool IsUnique = pModel.unique();
			pShootTrackModels.erase(pShootTrackModels.begin() + iModel);
			pModel.reset();

			m_pScene2D->SetTtrack1ShootModels(pShootTrackModels);
		}
	}

	/*if (TrackModels.size() == 1)
	{
		bool IsGenerate = false;
		pConditions->SetIsGenerate(IsGenerate);
	}*/
}

void C2DRender::ReloadLevel(TrackState InTrack)
{
	switch (InTrack)
	{
		case fOne:
		{
			auto pConditions = pMNGFigure->GetConditions();
			pConditions->SetIsGenerate(false);

			auto pCarModel = m_pScene2D->GetCurModel();
			auto offsetXY = pCarModel->GetOffset();
			pCarModel->SetOffset(fHorizontal, -offsetXY->x);
			pCarModel->SetOffset(fVertical, -offsetXY->y);

			auto RectLengthXY = pConditions->GetRectForCarInTrack();

			pCarModel->SetCurPositionXY(CPoint2D(RectLengthXY.lengthX + offsetXY->x, (pConditions->GetWINHEIGHT() / 2) + offsetXY->y));

			pConditions->SetCurGameTime(pConditions->GetFirstLevelTime());

			m_pScene2D->SetTrack1Models(std::vector<std::shared_ptr<C2DGenModel>>());

			break;
		}
	
		default:
			break;
	}

}

void C2DRender::RectBehaviour(std::shared_ptr<C2DGenModel> InModel)
{
	auto pRectProp = dynamic_cast<CProperty2DModel*>(InModel->GetProperty().get());
	auto pConditions = pMNGFigure->GetConditions();

	auto CurPosXY = InModel->GetCurPositionXY();
	auto MinMaxXY = InModel->GetMinMaxModelRect(InModel->GetObjects2D());
	auto wHeight = pConditions->GetWINHEIGHT();

	auto CerbHeight = pConditions->GetCerbHeight();

	//if ((((wHeight / 2) + CurPosXY->x + MinMaxXY.first.y) <= 50) || (((wHeight / 2) + CurPosXY->x + MinMaxXY.second.y) >= (1000)))//up cerb and bottom cerb
	//{
	//	int dX = InModel->GetdX();
	//	dX *= -1;
	//	InModel->SetdX(dX);
	//}
	int speed = pRectProp->GetSpeed();
	CurPosXY->x -= speed;//InModel->GetdX();
	InModel->SetCurPositionXY(CPoint2D(CurPosXY->x, CurPosXY->y));

}

void C2DRender::CycleBehaviour(std::shared_ptr<C2DGenModel> InModel)
{
	auto pCycleProp = dynamic_cast<CCycleProperty*>(InModel->GetProperty().get());
	auto CurPosXY = InModel->GetCurPositionXY();
	
	bool IsRebound = pCycleProp->GetIsRebound();
	auto Angel = pCycleProp->GetMoveAngel();
	int Speed = pCycleProp->GetSpeed();

	//Vertical
	auto pCondition = pMNGFigure->GetConditions();
	int CerbHeight = pCondition->GetCerbHeight();
	int wHeight = pCondition->GetWINHEIGHT();
	int wWidth = pCondition->GetWINWIDTH();

	auto Obj2D = InModel->GetObjects2D();

	auto pCycle = dynamic_cast<CCycle*>(Obj2D.front().get());
	int radius = static_cast<int>(pCycle->GetRadius());

	if (IsRebound)
	{

		int curPosY = static_cast<int>(wHeight / 2 + CurPosXY->y + radius);
		//if (curPosY > (wHeight - CerbHeight))
		if (CurPosXY->y > (wHeight - CerbHeight))
		{
			CurPosXY->y = static_cast<float>(wHeight - CerbHeight);
			IsRebound = false;
			pCycleProp->SetIsRebound(IsRebound);
		}
		else
		{
			//DOWN
			CurPosXY->x = static_cast<float>(CurPosXY->x - Speed * cos(Angel * M_PI / 180));
			CurPosXY->y = static_cast<float>(CurPosXY->y + Speed * sin(Angel * M_PI / 180));
		}
	}
	else
	{
		int curPosY = static_cast<int>(wHeight / 2 + CurPosXY->y - radius);
		
		//if (curPosY < CerbHeight)
		if (CurPosXY->y < CerbHeight)
		{
			CurPosXY->y = static_cast<float>(CerbHeight);
			IsRebound = true;
			pCycleProp->SetIsRebound(IsRebound);
		}
		else
		{
			//UP
			CurPosXY->x = static_cast<float>(CurPosXY->x - Speed * cos(Angel * M_PI / 180));
			CurPosXY->y = static_cast<float>(CurPosXY->y - Speed * sin(Angel * M_PI / 180));
		}
	}

	int curRadPosX = static_cast<int>(wWidth / 2 + CurPosXY->x);
	int curRadPosY = static_cast<int>(wHeight / 2 + CurPosXY->y);
}

void C2DRender::TrianBehavior(std::shared_ptr<C2DGenModel> InModel)
{
	auto pCondition = pMNGFigure->GetConditions();
	auto pTrianProp = dynamic_cast<CTriangleProperty*>(InModel->GetProperty().get());

	auto CurPosXY = InModel->GetCurPositionXY();	
	auto MinMaxXY = InModel->GetMinMaxModelRect(InModel->GetObjects2D());
	
	int wHeight = pCondition->GetWINHEIGHT();
	int wWidth = pCondition->GetWINWIDTH();

	auto CerbHeight = pCondition->GetCerbHeight();
	
	auto Obj2D = InModel->GetObjects2D();
	auto pTrian = dynamic_cast<CTriangle2D*>(Obj2D.front().get());

	//auto descrRect =pTrian->GetDescribedRect();

	auto DescrRect = pTrian->GetDescribedRect();
	auto CerbHight = pCondition->GetCerbHeight() * 2;

	int curPosY = wHeight / 2;// +CurPosXY->y;// +radius;

	if (((CurPosXY->y + MinMaxXY.first.y) <= CerbHight) || (( + CurPosXY->y + MinMaxXY.second.y) >= (wHeight - CerbHight)))//up cerb and bottom cerb
	{
		pTrianProp->SetIsUp(!pTrianProp->GetIsUp());
	}

	bool IsUp = pTrianProp->GetIsUp();
	int speed = pTrianProp->GetSpeed();
	int vertSpeed = 2;
	if (IsUp)
	{
		CurPosXY->y += vertSpeed*2;
		CurPosXY->x -= vertSpeed;
	}
	else
	{
		CurPosXY->y -= vertSpeed*2;
		CurPosXY->x -= vertSpeed;
	}
	
	InModel->SetCurPositionXY(CPoint2D(CurPosXY->x, CurPosXY->y));

}
