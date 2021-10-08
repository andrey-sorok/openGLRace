#ifndef __MYMATH_
#define __MYMATH_

class CPoint2D;

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
};

#endif //__MYMATH_