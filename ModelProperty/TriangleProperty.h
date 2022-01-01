#ifndef __TRIANGLEPROPERTY_
#define __TRIANGLEPROPERTY_

#include "Property2DModel.h"


class CTriangleProperty : public CProperty2DModel
{
private:
	bool m_IsUp;

public:
	CTriangleProperty();
	~CTriangleProperty();

	void SetIsUp(bool InIsUp) { m_IsUp = InIsUp; };
	bool GetIsUp() { return m_IsUp; };
};

#endif //__TRIANGLEPROPERTY_
