#ifndef __CONDITION_
#define __CONDITION_

#include "Types.h"

#include "Color3D.h"
#include "Point2D.h"

#include <string>
#include <vector>
#include <memory>
#include<list>

class C2DModel;

class CCondition
{
private:

	int m_WINWIDTH;// = 1000;
	int m_WINHEIGHT;// = 950;

	bool m_IsMouseMove;
	GameState m_CurGameState;

	TrackState m_CurTrackState;

	EFigure m_CurFigure;
	CColor3D m_CurColor;

	int m_MouseState;
	int m_MouseButton;

	std::string m_CarsFolder;
	int m_NumCars;

	int m_NumCurbs;

	float m_�urbOffset;

	int m_CerbHeight;

	int m_CurLoopDrawTrack1;

	double m_Left;
	double m_Right;
	double m_Up;
	double m_Down;

	std::vector<std::string> m_Paths2Models;

	std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> vOutModelsGreed;

public:
	CCondition();
	~CCondition();

	void SetWINWIDTH(int InWinWidth);
	int GetWINWIDTH() { return m_WINWIDTH; };

	void SetWINHEIGHT(int InWinHeight);
	int GetWINHEIGHT() { return m_WINHEIGHT; };

	bool GetIsMouseMove() { return m_IsMouseMove; };
	void SetIsMouseMove(bool InIsMouseMove) { m_IsMouseMove = InIsMouseMove; };

	GameState& GetCurGameState() { return m_CurGameState; };
	void SetCurGameState(GameState InState) { m_CurGameState = InState; };

	void SetCurFigure(EFigure InCurFigure) { m_CurFigure = InCurFigure; };
	EFigure GetCurFigure() { return m_CurFigure; };

	void SetCurColor(CColor3D InColor) { m_CurColor = InColor; };
	CColor3D GetCurColor() { return m_CurColor; };

	void SetMouseState(int state) { m_MouseState = state; };
	int GetMouseState() { return m_MouseState; };
	
	void SetMouseButtonState(int state) { m_MouseButton = state; };
	int GetMouseButtonState() { return m_MouseButton; };

	void SetCarsFolder(std::string InCarFolder) { m_CarsFolder = InCarFolder; };
	std::string GetCarsFolder() { return m_CarsFolder; };

	void SetNumCars(int InNumCars) { m_NumCars = InNumCars; };
	int& GetNumCars() { return m_NumCars; };

	void SetCurbs(int InCurbs) { m_NumCurbs = InCurbs; };
	int GetCurbs() { return m_NumCurbs; };

	void SetPaths2Models(const std::vector<std::string> InPath2ModelsFiles) { m_Paths2Models = InPath2ModelsFiles; };
	std::vector<std::string> GetPaths2Models() { return m_Paths2Models; };

	void SetOutModelsGreed(std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> InVector) { vOutModelsGreed = InVector; };
	std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> GetOutModelsGreed() { return vOutModelsGreed; };

	void SetOffset(float InOffset) { m_�urbOffset = InOffset; };
	float GetOffset() { return m_�urbOffset; };

	int GetCerbHeight() { return m_CerbHeight; };

	void SetCurLoopDrawTrack1(int InCurLoopDrawTrack) { m_CurLoopDrawTrack1 = InCurLoopDrawTrack; };
	int GetCurLoopDrawTrack1() { return m_CurLoopDrawTrack1; };

	void SetLeftRightUpBottom(double left, double right, double up, double down);
	std::list<double> GeteftRightUpBottom();
	
};

#endif //__CONDITION_