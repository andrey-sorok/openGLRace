#ifndef __POINT3D_
#define __POINT3D_

class CPoint3D
{
public:
	float x;
	float y;
	float z;

	CPoint3D() {};
	CPoint3D(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {};

	void operator()(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	bool SetRGB(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
};

#endif //__POINT3D_