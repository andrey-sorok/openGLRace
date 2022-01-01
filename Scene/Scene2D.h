#ifndef __SCENE2D_
#define __SCENE2D_

#include <vector>
#include <memory>
#include <tuple>

#include "Types.h"
#include "Color3D.h"

class CFigureBase;
class CColor3D;

class CPoint3D;
class CPoint2D;

class C2DModel;
class C2DGenModel;

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

	std::vector<std::shared_ptr<C2DGenModel>> m_Ttrack1Models;

	std::vector<std::shared_ptr<C2DModel>> m_Ttrack1ShootModels;

	int m_MaxTrackObjSpeed;
	int m_TimeAfter;
	
//End_Track

private:
	std::vector<std::shared_ptr<C2DGenModel>> Generate(int winWight, int winHeightint,
		int InNumObjectsGenerate, int InMaxTrackObj);

public:
	CScene2D();
	~CScene2D();

	//__
	void AddModel(std::shared_ptr<C2DModel> InModel);
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

	std::vector<std::shared_ptr<C2DGenModel>> GenerateTrack1Models(int winWight, int winHeight,
		std::tuple<int, int, int, int> InTrackTimeNumIntervalsOneTimreIntervalMaxCurLtrackObjects);

	void GenerateShootTrack1(int wHeight);

	void SetTtrack1ShootModels(std::vector<std::shared_ptr<C2DModel>> InTtrack1ShootModels) { m_Ttrack1ShootModels = InTtrack1ShootModels; };
	std::vector<std::shared_ptr<C2DModel>>& GetTtrack1ShootModels() { return m_Ttrack1ShootModels; };

	void SetTrack1Models(std::vector<std::shared_ptr<C2DGenModel>> InTtrack1Models) { m_Ttrack1Models = InTtrack1Models; };
	std::vector<std::shared_ptr<C2DGenModel>>& GetTrack1Models() { return m_Ttrack1Models; };

	int GetMaxTrackObjSpeed() { return m_MaxTrackObjSpeed; };

	void ClearCurModels();

};

#endif //__SCENE2D_