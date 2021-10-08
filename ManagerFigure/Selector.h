
#ifndef __SELECTOR_
#define __SELECTOR_

#include <vector>

#include "Color3D.h"

class CFigureBase;

class CSelector
{
private:
	CColor3D m_SelectColor;
	std::vector<CFigureBase*> m_SelectOjects2D;

public:
	CSelector();
	~CSelector();
	
	std::vector<CFigureBase*>& GetSelectObjects() { return m_SelectOjects2D; };
	void SetSelection(CFigureBase* pInFigure, CColor3D InCurColor);
};

#endif //__SELECTOR_