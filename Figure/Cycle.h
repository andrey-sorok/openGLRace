#pragma once
#include "FigureBase.h"

#include "Point2D.h"

class CCycle :
	public CFigureBase
{
private:

	CPoint2D m_Center;

	int m_NumSegments;
	double m_Radius;

	double m_Scale;

public:
	CCycle();
	~CCycle();

	CCycle(const CPoint2D inCenter, const double inRadius, CColor3D inColor);
	CCycle(const CPoint2D inCenter, CColor3D inColor);
	CCycle(const CPoint2D inCenter);

	CPoint2D GetCenter(){ return m_Center; };
	int GetNumSegments() { return m_NumSegments; };
	double GetRadius() { return m_Radius; };

	void SetDelta(const int inDeltaX, const int inDeltaY);
	void SetNewCoord(const int inX, const int inY);
	bool SetNewScale(bool IsUp);

	/*InCondition	- 0 SetNewScale
	- 1 SetNewDelta
	- 2 SetNewCoord
	*/
	bool CheckInWindow(int InCondition, bool IsUp, CPoint2D InCenterXY, int InWinWidth, int InWinHeight);

};

