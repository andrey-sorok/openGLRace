#ifndef __PROJMANAGER_
#define __PROJMANAGER_

#include <OpenGLRender.h>
#include <C2DRender.h>
#include <Condition.h>
#include <Scene2D.h>

#include <memory>

/*class CManager
{
protected:
	template<typename OutT>
	OutT CreateLmd(int InLmd);

}*/;

class CProjManager
{
protected:

	std::shared_ptr<COpenGLRender> m_OpenGlRender;

	std::shared_ptr<CCondition> m_Conditions;
	std::shared_ptr<C2DRender> m_2DRender;
	std::shared_ptr <CManagerFigure> m_FMGManager;
	std::shared_ptr<CScene2D> m_Scene2D;

	//std::vector<std::pair<int, std::function<std::vector<int(std::vector<int>)>>>> m_LmdFunctions;

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

//template<typename OutT>
//OutT CManager::CreateLmd(int InLmd)
//{
//	/*switch (InLmd)
//	{
//		case 1:
//		{
//			auto Lmd = []()
//			{
//				auto pConditions = m_ProjManager->GetConditions();
//	
//				auto pScene = m_ProjManager->GetScene();
//				auto pCurModel = pScene->GetCurModel();
//	
//				auto pCenter = pCurModel->GetCenter();
//				auto pMinMaxXY = pCurModel->GetMinMaxModelRect(pCurModel->GetObjects2D());
//	
//				auto RectForModelInTrack = pConditions->GetRectForCarInTrack();
//				double scaleX = pCurModel->GetScaleX();
//				double scaleY = pCurModel->GetScaleY();
//	
//				float lengthModelY = pMinMaxXY.second.x - pMinMaxXY.first.x;
//				float lengthModelX = pMinMaxXY.second.y - pMinMaxXY.first.y;
//	
//				float NewLengthX = lengthModelX * scaleX;
//				float NewLengthY = lengthModelY * scaleY;
//	
//				auto pCurPosition = pCurModel->GetCurPositionXY();
//	
//				int curX2 = pCurPosition->x + NewLengthX / 2;
//				int curY2 = pCurPosition->y + NewLengthY / 2;
//	
//				int curX1 = pCurPosition->x - NewLengthX / 2;
//				int curY1 = pCurPosition->y - NewLengthY / 2;
//	
//				std::list<int> rtnLst;
//				rtnLst.push_back(curX1);
//				rtnLst.push_back(curY1);
//	
//				rtnLst.push_back(curX2);
//				rtnLst.push_back(curY2);
//	
//				return rtnLst;
//			};
//		
//			std::function<std::list<int>> lmdF1 = Lmd;
//
//			return lmdF1;
//		}*/
//
//		/*case 2:
//		{
//			auto f = [](int i)
//			{
//				if (i < 0)
//					return 0;
//				if (i >= 0)
//					return 1;
//			};
//
//			std::function<std::list<int>> lmdF2 = f;
//
//			return lmdF2;
//
//		}
//	}*/
//
//	return 1;
//};
