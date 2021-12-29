#ifndef __2DGENMODEL_
#define __2DGENMODEL_

#include "C2DModel.h"
#include "Property2DModel.h"


class C2DGenModel : public C2DModel
{
private:

	int m_dX;
	int m_dY;

	std::shared_ptr<CProperty2DModel> m_Property;

public:

	C2DGenModel(eModelType InModelType, std::vector<std::shared_ptr<CFigureBase>> InFigureModel );

	~C2DGenModel();

	void SetdX(double IndX) { m_dX = static_cast<int>(IndX); };
	int GetdX() { return m_dX; };

	void SetdY(double IndY) { m_dY = static_cast<int>(IndY); };
	int GetdY() { return m_dY; };

	std::shared_ptr<CProperty2DModel> GetProperty() { return m_Property; };
};

#endif //__2DGENMODEL_
