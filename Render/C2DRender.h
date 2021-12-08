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
class C2DModel;

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
	void DrawMoveTrack1(TrackState InState);

	void Draw2DOject(CFigureBase* pInFigure);
	
	void Draw2DLine(CLine2D* pInFigure);

	void Circle(CColor3D* inColor, float cx, float cy, float r, int num_segments);
	
	void DrawRect2D(CRect2D* inRect);
	void DrawTriangle2D(CTriangle2D* inTriangle);
	void DrawCircle(CCycle* inCycle);

	void DrawAxes(CLine2D* inAbciss, CLine2D* inOrdinate);
	//Track Direction

	void KeyReDrowTrack(EDirect InDirec, int d);

private:
	void DrawCircle(CColor3D * inColor, float cx, float cy, float r, int num_segments);

	void DrawTrack1();
	void GeneRateCerb(std::shared_ptr<C2DModel> InModel);

};

#endif //__2DRENDER_
