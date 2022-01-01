#ifndef __PROJMANAGER_
#define __PROJMANAGER_

#include <OpenGLRender.h>
#include <C2DRender.h>
#include <Condition.h>
#include <Scene2D.h>

#include <memory>

class CProjManager
{
protected:

	std::shared_ptr<COpenGLRender> m_OpenGlRender;

	std::shared_ptr<CCondition> m_Conditions;
	std::shared_ptr<C2DRender> m_2DRender;
	std::shared_ptr <CManagerFigure> m_FMGManager;
	std::shared_ptr<CScene2D> m_Scene2D;


public:

	CProjManager();
	~CProjManager();

	std::shared_ptr<CCondition> GetConditions() { return m_Conditions; };
	void SetConditions(std::shared_ptr<CCondition> InConditions) { m_Conditions.reset(InConditions.get()); };

	std::shared_ptr<C2DRender> Get2DRender() { return m_2DRender; };
	void Set2DRender(std::shared_ptr<C2DRender> InConditions) { m_2DRender.reset(InConditions.get()); };

	std::shared_ptr<CManagerFigure> GetFMGManager() { return m_FMGManager; };
	void SetFMGManager(std::shared_ptr<CManagerFigure> InConditions) { m_FMGManager.reset(InConditions.get()); };

	std::shared_ptr<CScene2D> GetScene() { return m_Scene2D; };
	void SetScene(std::shared_ptr<CScene2D> InConditions) { m_Scene2D.reset(InConditions.get()); };

};

#endif //__PROJMANAGER_

