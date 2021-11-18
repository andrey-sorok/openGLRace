#ifndef __TYPES_
#define __TYPES_

enum EFigure 
{ 
	fPoint,		//0
	fLine,		//1
	fTriangle,	//2
	fRectangle, //3
	fCycle,		//4
	fCube,		//5
	fNone,		//6
};

enum GameState
{
	BeginLoading,	//0
	StartMenu,		//1
	Redact,			//2
	Game,			//3
	Choice			//4
};

enum fileAccess { in, out, inout };

#endif //
