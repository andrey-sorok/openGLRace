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

enum TrackState
{
	fNoneTrack,		//0
	fOne,			//1
	fTwo,			//2
	fThree			//3
};

enum EDirect
{
	fHorizontal,		//0
	fVertical,			//1
};

enum eModelType
{
	mCar,			//0
	m—urb,			//1
	mRect,			//2
	mCycle,			//3
	mTriangle,		//4
	m—omposite,		//5
};


enum fileAccess { in, out, inout };

struct RectForCarInTrack
{
	float lengthX;
	float lengthY;
};

#endif //
