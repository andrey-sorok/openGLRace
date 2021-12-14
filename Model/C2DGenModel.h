#ifndef __2DGENMODEL_
#define __2DGENMODEL_

#include "C2DModel.h"


class C2DGenModel : public C2DModel
{
private:
	int m_dX;
	int m_dY;
public:

	C2DGenModel( std::vector<std::shared_ptr<CFigureBase>> InFigureModel );

	~C2DGenModel();

	void SetdX(double IndX) { m_dX = static_cast<int>(IndX); };
	int GetdX() { return m_dX; };

	void SetdY(double IndY) { m_dY = static_cast<int>(IndY); };
	int GetdY() { return m_dY; };
};

#endif //__2DGENMODEL_
