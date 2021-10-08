#include "MyMath.h"

#include "Point2D.h"

CMyMath::CMyMath()
{
}


CMyMath::~CMyMath()
{
}

bool CMyMath::IsPointLocation(const CPoint2D InVecBegin, const CPoint2D InVecEnd, const CPoint2D InPoint)
{
	double res = (InVecEnd.x - InVecBegin.x)*(InPoint.y - InVecBegin.y) - (InVecEnd.y - InVecBegin.y) * (InPoint.x - InVecBegin.x);
	bool IsLeft = false;
	if (res < 0.01)
	{
		IsLeft = true;
	}
	//bool IsLeft = (res < 0.01) ? false : true;
	return IsLeft;
}

bool CMyMath::IsPointInTriangle(const CPoint2D InVec1Begin, const CPoint2D InVec1End, const CPoint2D InVec2Begin,
	const CPoint2D InVec2End, const CPoint2D InVec3Begin,
	const CPoint2D InVec3End, const CPoint2D InPoint)
{
	bool rtn = false;

	bool IsLeft1 = IsPointLocation(InVec1Begin, InVec1End, InPoint);
	bool IsLeft2 = IsPointLocation(InVec2Begin, InVec2End, InPoint);
	bool IsLeft3 = IsPointLocation(InVec3Begin, InVec3End, InPoint);

	if (!IsLeft1 && !IsLeft2 && !IsLeft3)
		rtn = true;

	return rtn;
}