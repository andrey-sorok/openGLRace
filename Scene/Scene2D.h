#ifndef __SCENE2D_
#define __SCENE2D_

#include <vector>
#include <memory>

#include "Types.h"
#include "Color3D.h"

class CFigureBase;
class CColor3D;

class CPoint3D;
class CPoint2D;

class C2DModel;

class CScene2D
{
private:
	std::vector<std::shared_ptr<CFigureBase>> m_LeftSideBarObj;

	std::vector<std::shared_ptr<CFigureBase>> m_StartMenuObj;

	std::vector<std::shared_ptr<CFigureBase>> GetLeftSideBarObj();

	std::vector<std::shared_ptr<CFigureBase>> GetStartMenObj();

	std::vector<std::vector<std::shared_ptr<CFigureBase>>> m_vCarsModels;

//Track
	std::shared_ptr<C2DModel> m_Ñurb;

	std::vector<std::shared_ptr<C2DModel>> m_vModels;
	std::shared_ptr<C2DModel> m_CurTrackModel;
	
//End_Track

private:


public:
	CScene2D();
	~CScene2D();

	//__
	void AddModel(std::shared_ptr<C2DModel> InrModel);
	std::vector<std::shared_ptr<C2DModel>> GetModels() { return m_vModels; };
	std::shared_ptr<C2DModel> GetModel(int InNumModel);
	//__

	void AddCarModels(std::vector<std::shared_ptr<CFigureBase>> InCarModels);
	std::vector<std::vector<std::shared_ptr<CFigureBase>>> GetCarModels() { return m_vCarsModels; };

	std::vector<std::shared_ptr<CFigureBase>> GetDrawRedactObjCondition();
	
	std::vector<std::shared_ptr<CFigureBase>> GetDrawStartMenuObjCondition();
	
	bool IsLeftSideBarClick(int InX, int InY);

	EFigure GetFigureClick(int InX, int InY);

	bool ChecClickSaveAndExit(int InX, int InY);

	bool ChecClickSave(int InX, int InY);

	CColor3D GetClickColor(int InX, int InY);

	GameState CheckStartMenuClick(CPoint3D InPointClick);

	std::shared_ptr<C2DModel> GetChoceModel(std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> vPointGrid, CPoint3D p);

	void SetCurModel(std::shared_ptr<C2DModel> InCurModel) { m_CurTrackModel = InCurModel; };
	std::shared_ptr<C2DModel> GetCurModel() { return m_CurTrackModel; };

	void GenerateCurdModel(int WinWidth, int InCerbHeight);

	std::shared_ptr<C2DModel> GetCurb() { return m_Ñurb; };

};

#endif //__SCENE2D_