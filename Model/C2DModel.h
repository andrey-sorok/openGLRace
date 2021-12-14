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
protected:
	std::list<std::shared_ptr<CFigureBase>> m_Objects2D;

	int m_iP;
	
	CPoint2D* m_CurPositionXY;

	CPoint2D* m_CenterXY;

	CPoint2D* m_MinXY;
	CPoint2D* m_MaxXY;

	CPoint2D* m_OffsetXY;

	double m_ScaleX;
	double m_ScaleY;

	int m_LenghtModel;

	int m_TimeSet1;

public:
	//C2DModel();
	~C2DModel();

	C2DModel(std::vector<std::shared_ptr<CFigureBase>> InFigureModel);

	void Add2Objects2D(std::shared_ptr<CFigureBase> InObj2D);
	std::list<std::shared_ptr<CFigureBase>>& GetObjects2D() { return m_Objects2D; };

	std::list<float> GetVertex();

	std::pair<void*, void*> GetVertexArr(std::shared_ptr<CFigureBase> InObjects2D);

	std::pair<void*, void*> C2DModel::GetAllVrtAndColor(std::list<std::shared_ptr<CFigureBase>> InArrObjects2D, int& rtnSize);

	std::pair<float, float> GetCenter();

	std::pair<CPoint2D, CPoint2D> GetMinMaxRectXY();

	void SetiP(int IniP) { m_iP = IniP; };

	void SetOffset(EDirect InDirect,  float d);
	CPoint2D* GetOffset() { return m_OffsetXY; };

	void SetOffset(EDirect InDirect, CPoint2D InOffset);

	void SetCurPositionXY(CPoint2D InCurPositionXY);
	CPoint2D* GetCurPositionXY() { return m_CurPositionXY; };

	void SetLenghtModel(int InLenghtModel) { m_LenghtModel = InLenghtModel;	};
	int GetLenghtModel() { return m_LenghtModel; };

	void SetTimeSet1(int InTimeSet1) { m_TimeSet1 = InTimeSet1; };
	int GetTimeSet1() { return m_TimeSet1; };

	std::pair<CPoint2D, CPoint2D> GetMinMaxModelRect(std::list<std::shared_ptr<CFigureBase>> & InModelObjects2D);

	void SetScaleX(double InScaleX) { m_ScaleX = InScaleX; };
	double GetScaleX() { return m_ScaleX; };

	void SetScaleY(double InScaleY) { m_ScaleY = InScaleY; };
	double GetScaleY() { return m_ScaleY; };

protected:

	std::pair<double, double> CalcCenterModel(std::list<std::shared_ptr<CFigureBase>>& ModelObjects2D);

	void SetMinMaxRectXY(std::pair<CPoint2D, CPoint2D> MinMaxPoint);	
};

#endif //2DMODEL