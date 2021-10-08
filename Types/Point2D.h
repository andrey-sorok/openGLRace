#ifndef __POINT2D_
#define __POINT2D_

class CPoint2D
{
public:
	float x;
	float y;

	CPoint2D() {};
	CPoint2D(float inX, float inY) : x(inX), y(inY) {};

	void operator()(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	bool SetRGB(float inX, float inY)
	{
		x = inX;
		y = inY;
	}
};

#endif //__POINT2D_