#ifndef __2DRENDER_
#define __2DRENDER_

#include <vector>

#include "OpenGLRender.h"
#include "ManagerFigure.h"

#include "Types.h"

class CPoint2D;
class CColor3D;

class CRect2D;
class CTriangle2D;
class CCycle;
class CLine2D;

class CScene2D;

class C2DRender :public COpenGLRender
{
private:
	std::shared_ptr<CManagerFigure> pMNGFigure;

	std::shared_ptr<CScene2D> m_pScene2D;

	void DrawCurrenFigure(EFigure InCurFigure, CColor3D InColor);

	void renderSpacedBitmapString(float x, float y, int spacing, void *font, char *string);


public:
	C2DRender();
	~C2DRender();

	void SetFigureManager(std::shared_ptr<CManagerFigure> InMNGFigure);
	
	std::shared_ptr<CScene2D> GetScene2D() { return m_pScene2D; };
	
	void Draw(GameState InGameState);
	void DrawExistingModels();
	void DrawRedactComponents();
	void DrawStartMenu();

	void Draw2DOject(CFigureBase* pInFigure);
	
	void Draw2DLine(CLine2D* pInFigure);

	void Circle(CColor3D* inColor, float cx, float cy, float r, int num_segments);
	
	void DrawRect2D(CRect2D* inRect);
	void DrawTriangle2D(CTriangle2D* inTriangle);
	void DrawCircle(CCycle* inCycle);

	void DrawAxes(CLine2D* inAbciss, CLine2D* inOrdinate);

	//MOVE
	template<typename TFigure>
	void MoveOnLine(TFigure pFigure);

	template<typename TFigure>
	void MoveOnCycle(TFigure pFigure);
	//END_MOVE

private:
	void DrawCircle(CColor3D * inColor, float cx, float cy, float r, int num_segments);

};

#endif //__2DRENDER_

template<typename TFigure>
void C2DRender::MoveOnLine(TFigure pFigure)
{
	std::list<CPoint2D*> pListPoints = pFigure->GetPoints();
	int sizePoints = pListPoints.size();
	for (int iPoint = 0; iPoint < sizePoints; ++iPoint)
	{
		CPoint2D* pPoint = pListPoints.front();
		pListPoints.pop_front();

		pPoint->x += 1.00;
	}

}

template<typename TFigure>
inline void C2DRender::MoveOnCycle(TFigure pFigure)
{

	glRotatef(10, 10, 0, 0);
	//std::list<CPoint2D*> pListPoints = pFigure->GetPoints();
	//int sizePoints = pListPoints.size();
	//for (int iPoint = 0; iPoint < sizePoints; ++iPoint)
	//{
	//	CPoint2D* pPoint = pListPoints.front();
	//	pListPoints.pop_front();

	//	float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
	//	float x = r * cosf(theta);//calculate the x component 
	//	float y = r * sinf(theta);//calculate the y component 
	//	//glVertex2f(x + cx, y + cy);//output vertex 
	//}
}
