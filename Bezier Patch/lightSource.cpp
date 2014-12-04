#include "lightSource.h"
#include "window.h"
#include "main.h"
#include <GL/glut.h>

lightSource::lightSource()
{
	for (int i = 0; i < 4; i++) {
		ambient[i] = 0;
		specular[i] = 0;
		position[i] = 0;
		if (i != 3) {
			direction[i] = 0;
		}
	}
    constantAttenuation = 0;
	linearAttenuation = 0;
	quadraticAttenuation = 0;
	spotCutoff = 0;
	spotExponent = 0;
}
lightSource::lightSource( int post)
{
	pos = post;	
	for (int i = 0; i < 4; i++) {
		ambient[i] = 0;
		specular[i] = 0;
		position[i] = 0;
		if (i != 3) {
			direction[i] = 0;
		}
	}
	constantAttenuation = 0;
	linearAttenuation = 0;
	quadraticAttenuation = 0;
	spotCutoff = 0;
	spotExponent = 0;
}

lightSource::~lightSource()
{
}

void lightSource::draw() {
	glMatrixMode(GL_MODELVIEW);
	Matrix4 translate;
	translate.identity();
	translate.makeTranslate(position[0],position[1],position[2]);
	glColor3d(1,1,1);
	if (type == 0) {
		translate.transpose();
		glLoadMatrixd(translate.getPointer());
		glutSolidSphere(1, 20, 20);
	}
	else if (type == 1) {
		Matrix4 temp;
		Vector3 direct;
		direct.set(direction[0], direction[1], direction[2]);
		double angle = direct.dot(direct, Vector3(0, -1, 0));
		angle = angle / direct.length();
		angle = acos(angle) * 180 / M_PI;
		temp.makeRotateZ(angle);
		translate = translate * temp;
		temp.makeRotateX(-90);
		translate = translate * temp;
		translate.transpose();
		glLoadMatrixd(translate.getPointer());
		double radius = 1 * tan(spotCutoff*M_PI / 180);
		glutSolidCone(radius, 1, 20, 20);
	}
	glFlush();
}
