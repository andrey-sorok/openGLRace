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

public:
	//C2DModel();
	~C2DModel();

	C2DModel(std::vector<std::shared_ptr<CFigureBase>> InFigureModel);

	void Add2Objects2D(std::shared_ptr<CFigureBase> InObj2D);
	std::list<std::shared_ptr<CFigureBase>> GetObjects2D() { return m_Objects2D; };

	std::list<float> GetVertex();

	std::pair<void*, void*> GetVertexArr(std::shared_ptr<CFigureBase> InObjects2D);

	std::pair<void*, void*> C2DModel::GetAllVrtAndColor(std::list<std::shared_ptr<CFigureBase>> InArrObjects2D, int& rtnSize);

	/*void Rotate(double Angle);*/
	void Translate(double InX, double InY);

private:

	//std::pair<double, double> GetCenterModel();
	
};

#endif //2DMODEL

//void glVertexPointer(GLint size, GLenum type,
//	GLsizei stride, void* ptr)
//	
//void glNormalPointer(GLenum type, GLsizei stride,
//	void  *pointer)
//void glColorPointer(GLint size, GLenum type,
//	GLsizei stride, void *pointer)