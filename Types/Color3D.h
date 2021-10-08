#ifndef __COLOR3D_
#define __COLOR3D_

class CColor3D
{
public:
	unsigned int R;
	unsigned int G;
	unsigned int B;

	CColor3D() {};
	CColor3D(unsigned int inR, unsigned int inG, unsigned int inB) : R(inR), G(inG), B(inB) {};


	void operator()(unsigned int inR, unsigned int inG, unsigned int inB)
	{
		R = inR;
		G = inG;
		B = inB;
	}

	bool SetRGB(unsigned int inR, unsigned int inG, unsigned int inB)
	{
		R = inR;
		G = inG;
		B = inB;

		return true;
	}
};

#endif //__COLOR3D_