#include "C2DGenModel.h"

#include "CycleProperty.h"
#include "TriangleProperty.h"


C2DGenModel::C2DGenModel(eModelType InModelType, std::vector<std::shared_ptr<CFigureBase>> InFigureModel): 
	C2DModel(InModelType, InFigureModel)
{

	if (InModelType == mCycle)
	{
		m_Property = std::make_shared<CCycleProperty>();
	}
	else if (InModelType == mRect)
	{
		m_Property = std::make_shared<CProperty2DModel>();
	}
	else if (InModelType == mTriangle)
	{
		m_Property = std::make_shared<CTriangleProperty>();
	}

	m_dX = 2;
	m_dY = 2;
}

C2DGenModel::~C2DGenModel()
{
}
