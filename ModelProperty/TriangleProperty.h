#pragma once
#include "D:\MyExperiments\OpenGL\openGLRace\ModelProperty\Property2DModel.h"
class CTriangleProperty : public CProperty2DModel
{
private:
	bool m_IsUp;

public:
	CTriangleProperty();
	~CTriangleProperty();

	void SetIsUp(int InIsUp) { m_IsUp = InIsUp; };
	bool GetIsUp() { return m_IsUp; };
};

