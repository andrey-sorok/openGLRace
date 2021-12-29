#ifndef __KEYBOARD_
#define __KEYBOARD_

#include <ProjManager.h>

#include <memory>

class CManagerFigure;

class CKeyBoard
{
private:
	std::shared_ptr<CProjManager> m_ProjManager;

public:
	CKeyBoard();
	~CKeyBoard();

	void SetProjManager(std::shared_ptr<CProjManager> InProjManager);

	void KeyProcess(int key, int x, int y);
	void KeyStroke(unsigned char key, int x, int y);

private:

	void TrackProcess(int key, int x, int y);

};

#endif //__KEYBOARD_