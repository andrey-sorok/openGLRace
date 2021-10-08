#include "CoordTransform.h"

#include <GL\glew.h>
#include <GL\freeglut.h>

#include "Point3D.h"

CCoordTransform::CCoordTransform()
{
}

CCoordTransform::~CCoordTransform()
{
}

CPoint3D CCoordTransform::Win2ProjCoordinate(const int x, const int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX = 0, posY = 0, posZ = 0;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);//LOOK
	glGetDoublev(GL_PROJECTION_MATRIX, projection);//LOOK
	glGetIntegerv(GL_VIEWPORT, viewport);//LOOK

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);//LOOK

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	CPoint3D ret;
	ret.x = posX;
	ret.y = posY;
	ret.z = posZ;
	return ret;
}

void CCoordTransform::ChangeSize(int w, int h, int& WINWIDTH, int& WINHEIGHT, double m_OrthoMinX, double m_OrthoMaxX, double m_OrthoMinY, double m_OrthoMaxY)
{
	int& window_width = WINWIDTH;
	int& window_height = WINHEIGHT;

	GLfloat aspectRatio;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h) {
		window_width = 1000;
		window_height = 1000 / aspectRatio;
		glOrtho(m_OrthoMinX, m_OrthoMaxX, -window_height, window_height, 1.0, -1.0);
	}
	else {
		window_width = 1000 * aspectRatio;
		window_height = 1000;
		glOrtho(-window_width, window_width, m_OrthoMinY, m_OrthoMaxY, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
