#ifndef __FIGUREBASE_
#define __FIGUREBASE_

#include "Color3D.h"
#include "Types.h"

class CFigureBase
{
protected:
	CColor3D m_Color;
	int m_IndOjects2D;
	EFigure m_fType;

public:
	CFigureBase();
	virtual ~CFigureBase();

	EFigure GetType() { return m_fType; };
	void SetType(EFigure inType) { m_fType = inType; };

	void SetColor(CColor3D inColor);
	CColor3D * GetColor();

	void SetIndObject2D(int Ind);
	int GetIndObject2D();
};

#endif //__FIGUREBASE_
