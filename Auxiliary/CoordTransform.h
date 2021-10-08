#ifndef __COORDTRANSFORM_
#define __COORDTRANSFORM_


class CPoint3D;

//class GLsizei;
//class CCoordTransform;

class CCoordTransform
{
public:
	CCoordTransform();
	~CCoordTransform();

	CPoint3D Win2ProjCoordinate(const int x, const int y);
	void ChangeSize(int w, int h, int& WINWIDTH, int& WINHEIGHT, double m_OrthoMinX, double m_OrthoMaxX,
		double m_OrthoMinY, double m_OrthoMaxY);
};

#endif //__COORDTRANSFORM_