#ifndef __2DMODEL_
#define __2DMODEL_

#include <list>
#include <vector>
#include <memory>


class CFigureBase;

class C2DModel
{
private:
	std::list<std::shared_ptr<CFigureBase>> m_Objects2D;

	int m_iP;

	int m_Center_X;
	int m_Center_Y;

public:
	//C2DModel();
	~C2DModel();

	C2DModel(std::vector<std::shared_ptr<CFigureBase>> InFigureModel);

	void Add2Objects2D(std::shared_ptr<CFigureBase> InObj2D);
	std::list<std::shared_ptr<CFigureBase>> GetObjects2D() { return m_Objects2D; };

	std::list<float> GetVertex();

	std::pair<void*, void*> GetVertexArr(std::shared_ptr<CFigureBase> InObjects2D);

	std::pair<void*, void*> C2DModel::GetAllVrtAndColor(std::list<std::shared_ptr<CFigureBase>> InArrObjects2D, int& rtnSize);

	std::pair<double, double> GetCenter() { return std::make_pair(m_Center_X, m_Center_Y); };

	/*void Rotate(double Angle);*/
	//void Translate(double InX, double InY);

	std::pair<double, double> CalcCenterModel(std::list<std::shared_ptr<CFigureBase>>& ModelObjects2D);

private:
	
};

#endif //2DMODEL