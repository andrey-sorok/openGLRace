#ifndef __MOUSE_
#define __MOUSE_

#define _CRT_SECURE_NO_WARNINGS

#include <memory>

class CManagerFigure;
class CScene2D;

class CPoint3D;

class CProjManager;

class CMouse
{
private:

	std::shared_ptr<CProjManager> m_ProjManager;
	std::shared_ptr<CManagerFigure> pMNGFigure;
	std::shared_ptr<CScene2D> m_pScene2D;

public:
	CMouse();
	~CMouse();

	void SetFigureManager(std::shared_ptr<CManagerFigure> InMNGFigure);
	void SetScene2D(std::shared_ptr<CScene2D> InScene2d);

	void MouseClick(int button, int state, int x, int y, bool& InIsMouseMove);
	void MouseMotion(int x, int y, bool& InIsMouseMove);
	void MousePassiveMotion(int x, int y);
};

#endif //__MOUSE_