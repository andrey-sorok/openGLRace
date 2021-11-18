#ifndef __MYMATH_
#define __MYMATH_

#include <vector>

class CPoint2D;
class CFigureBase;

class CMyMath
{
public:
	CMyMath();
	~CMyMath();

	bool IsPointLocation(const CPoint2D InVecBegin, const CPoint2D InVecEnd, const CPoint2D InPoint);
	bool IsPointInTriangle(const CPoint2D InVec1Begin, const CPoint2D InVec1End,
		const CPoint2D InVec2Begin, const CPoint2D InVec2End,
		const CPoint2D InVec3Begin, const CPoint2D InVec3End,
		const CPoint2D InPoint);

	bool CheckFiguresConnectivity(std::vector<CFigureBase*> InObjVector);
	std::vector<CFigureBase*> GetConnectObjs(std::vector<CFigureBase*> &InObjVector, CFigureBase* InUpObj);
	bool ChecRectDescribed(CFigureBase* InUpObj1, CFigureBase* InUpObj2);

	//Figures rectangle described
	std::pair<CPoint2D, CPoint2D> GetRectangleRectDescribed(CFigureBase* InRect);
	std::pair<CPoint2D, CPoint2D> GetTriangleRectDescribed(CFigureBase* InTrian);
	std::pair<CPoint2D, CPoint2D> GetCucleRectDescribed(CFigureBase* InCycle);

	std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> CreateOutGreed(int InNumModels, int WinWidth, int WinHeight);

private:
	std::vector<std::vector<std::pair<CPoint2D, CPoint2D>>> CalcGreed(int WidthCell, int HeightRow, int rows, int cols);

};

#endif //__MYMATH_