#ifndef __KEYBOARD_
#define __KEYBOARD_

#include <memory>

class CManagerFigure;

class CKeyBoard
{
private:
	std::shared_ptr<CManagerFigure> pMNGFigure;

public:
	CKeyBoard();
	~CKeyBoard();

	void SetFigureManager(std::shared_ptr<CManagerFigure> InMNGFigure);

	void KeyProcess(int key, int x, int y);
	void KeyStroke(unsigned char key, int x, int y);
};

#endif //__KEYBOARD_