#ifndef __2DMODEL_
#define __2DMODEL_

#include "Types.h"

#include <list>
#include <vector>
#include <memory>


class CFigureBase;
class CPoint2D;

class C2DModel
{
private:
	std::list<std::shared_ptr<CFigureBase>> m_Objects2D;

	int m_iP;

	int m_Center_X;
	int m_Center_Y;

	int m_minX;
	int m_minY;

	int m_maxX;
	int m_maxY;

	CPoint2D* m_CenterXY;

	CPoint2D* m_MinXY;
	CPoint2D* m_MaxXY;

	CPoint2D* m_OffsetXY;

public:
	//C2DModel();
	~C2DModel();

	C2DModel(std::vector<std::shared_ptr<CFigureBase>> InFigureModel);

	void Add2Objects2D(std::shared_ptr<CFigureBase> InObj2D);
	std::list<std::shared_ptr<CFigureBase>> GetObjects2D() { return m_Objects2D; };

	std::list<float> GetVertex();

	std::pair<void*, void*> GetVertexArr(std::shared_ptr<CFigureBase> InObjects2D);

	std::pair<void*, void*> C2DModel::GetAllVrtAndColor(std::list<std::shared_ptr<CFigureBase>> InArrObjects2D, int& rtnSize);

	std::pair<double, double> GetCenter() { return std::make_pair(m_Center_X, m_Center_Y); };

	std::pair<CPoint2D, CPoint2D> GetMinMaxRectXY();

	void SetiP(int IniP) { m_iP = IniP; };

	void SetOffset(EDirect InDirect,  float d);
	CPoint2D* GetOffset() { return m_OffsetXY; };

private:

	std::pair<double, double> CalcCenterModel(std::list<std::shared_ptr<CFigureBase>>& ModelObjects2D);

	void SetMinMaxRectXY(std::pair<CPoint2D, CPoint2D> MinMaxPoint);	
};

#endif //2DMODEL