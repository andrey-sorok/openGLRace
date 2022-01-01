#ifndef __CYCLEPROPERTY_
#define __CYCLEPROPERTY_

#include "Property2DModel.h"


class CCycleProperty : public CProperty2DModel
{
private:
	double m_MoveAngel;
	bool m_IsRebound;

public:
	CCycleProperty();
	~CCycleProperty();

	void SetMoveAngel(double InMoveAngel) { m_MoveAngel = InMoveAngel; };
	double GetMoveAngel() { return m_MoveAngel; };

	void SetIsRebound(bool IndIsRebound) { m_IsRebound = IndIsRebound; };
	bool GetIsRebound() { return m_IsRebound; };

};

#endif //__CYCLEPROPERTY_
