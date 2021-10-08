#ifndef __CONDITION_
#define __CONDITION_

#include "Types.h"

#include "Color3D.h"

class CCondition
{
private:

	int m_WINWIDTH;// = 1000;
	int m_WINHEIGHT;// = 950;

	bool m_IsMouseMove;
	GameState m_CurGameState;

	EFigure m_CurFigure;
	CColor3D m_CurColor;

	int m_MouseState;
	int m_MouseButton;

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
};

#endif //__CONDITION_