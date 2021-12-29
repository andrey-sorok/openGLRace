#ifndef __PROPERTY2DMODEL_
#define __PROPERTY2DMODEL_


class CProperty2DModel
{
protected:
	int m_Speed;
	int m_ShowAfterTime;

public:
	CProperty2DModel();
	virtual ~CProperty2DModel();

	void SetSpeed(int IndX) { m_Speed = IndX; };
	int GetSpeed() { return m_Speed; };

	void SetShowAfterTime(int InShowAfterTime) { m_ShowAfterTime = InShowAfterTime; };
	int GetShowAfterTime() { return m_ShowAfterTime; };
};


#endif //__PROPERTY2DMODEL_
