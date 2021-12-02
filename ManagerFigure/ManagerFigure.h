
#ifndef __MANAGERFIGURE_
#define __MANAGERFIGURE_

#include "FigureBase.h"

#include <vector>
#include <memory>

class CSelector;
class CCondition;

class CManagerFigure
{
private:
	unsigned int m_NumObjects;

protected:
	std::vector<CFigureBase*> m_Ojects2D;
	std::unique_ptr<CSelector> m_Selector;

	std::shared_ptr<CCondition> m_pConditions;

public:
	CManagerFigure();
	~CManagerFigure();

	std::unique_ptr<CSelector> GetSelector();

	void SetConditions(std::shared_ptr<CCondition> InConditions) { m_pConditions.reset(InConditions.get()); };
	std::shared_ptr<CCondition> GetConditions() { return m_pConditions; };

	void CreateNewFigure(int x, int y);
	void CreateNewFigure(int InX, int InY, EFigure InCurFigure);

	std::vector<CFigureBase*>& GetObjects() { return m_Ojects2D; };
	bool AddObject2D(CFigureBase* inFigure);
	CFigureBase * GetObject2D(int Ind);

	std::vector<CFigureBase*> GetAll2DObjects() { return m_Ojects2D;	};

	void SetIndObjecyt2D(CFigureBase * inFigure);

	bool ClickedObj2D(int x, int y);

	int GetObjecs2DSize() { return m_Ojects2D.size(); };
	bool SetNewCoord(int x, int y);

	bool SetNewCoord(bool IsMouse, const int x, const int y);
	bool SetNewScale(bool IsUp);

	bool RemoveAllSelectFigures(std::vector<CFigureBase*>& Objects2D);
};

#endif //__MANAGERFIGURE_

