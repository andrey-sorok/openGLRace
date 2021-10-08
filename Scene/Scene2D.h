#ifndef __SCENE2D_
#define __SCENE2D_

#include <vector>
#include <memory>

#include "Types.h"
#include "Color3D.h"

class CFigureBase;
class CColor3D;

class CPoint3D;

class CScene2D
{
private:
	std::vector<std::shared_ptr<CFigureBase>> m_LeftSideBarObj;

	std::vector<std::shared_ptr<CFigureBase>> m_StartMenuObj;

	std::vector<std::shared_ptr<CFigureBase>> GetLeftSideBarObj();

	std::vector<std::shared_ptr<CFigureBase>> GetStartMenObj();

public:
	CScene2D();
	~CScene2D();

	std::vector<std::shared_ptr<CFigureBase>> GetDrawRedactObjCondition();
	
	std::vector<std::shared_ptr<CFigureBase>> GetDrawStartMenuObjCondition();
	
	bool IsLeftSideBarClick(int InX, int InY);

	EFigure GetFigureClick(int InX, int InY);

	bool ChecClickSaveAndExit(int InX, int InY);

	CColor3D GetClickColor(int InX, int InY);

	GameState CheckStartMenuClick(CPoint3D InPointClick);
};

#endif //__SCENE2D_