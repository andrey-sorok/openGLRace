#include "C2DGenModel.h"


C2DGenModel::C2DGenModel(std::vector<std::shared_ptr<CFigureBase>> InFigureModel): C2DModel(InFigureModel)
{
	m_dX = 0;
	m_dY = 2;
}

C2DGenModel::~C2DGenModel()
{
}
