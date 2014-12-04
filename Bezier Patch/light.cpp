#include "light.h"
#include "GL/glut.h"
#include "main.h"
light::light()
{
	for (int i = 0; i < 8; i++) {
		lightSource *temp = new lightSource(i);
		lights.push_back(*temp);
	}
}


light::~light()
{
}

void light::setType(int i, int j) {
	lights[i].type = j;
}
void light::setAmbient(int i, float a, float b, float c, float d){
	lights[i].ambient[0] = a;
	lights[i].ambient[1] = b;
	lights[i].ambient[2] = c;
	lights[i].ambient[3] = d;
}
void light::setDiffuse(int i, float a, float b, float c, float d){
	lights[i].diffuse[0] = a;
	lights[i].diffuse[1] = b;
	lights[i].diffuse[2] = c;
	lights[i].diffuse[3] = d;
}
void light::setSpecular(int i, float a, float b, float c, float d){
	lights[i].specular[0] = a;
	lights[i].specular[1] = b;
	lights[i].specular[2] = c;
	lights[i].specular[3] = d;
}
void light::setPosition(int i, float a, float b, float c, float d){
	lights[i].position[0] = a;
	lights[i].position[1] = b;
	lights[i].position[2] = c;
	lights[i].position[3] = d;
}
void light::setDirection(int i, float a, float b, float c){
	lights[i].direction[0] = a;
	lights[i].direction[1] = b;
	lights[i].direction[2] = c;
}
void light::setAttenuation(int i, double a, double b, double c){
	lights[i].constantAttenuation = a;
	lights[i].linearAttenuation = b;
	lights[i].quadraticAttenuation = c;
}
void light::setSpotCutoff(int i, double a){
	lights[i].spotCutoff = a;
}
void light::setSpotExponent(int i, double a){
	lights[i].spotExponent = a;
}
void light::turnOn(int i) {
	glMatrixMode(GL_MODELVIEW);
	Matrix4 translate;
	translate.identity();
	translate.transpose();
	glLoadMatrixd(translate.getPointer());
	switch (i) {
	case 0:
		lights[0].draw();
		if (lights[0].type == 0) {
			glLightfv(GL_LIGHT0, GL_AMBIENT, lights[0].ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lights[0].diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, lights[0].specular);
			glLightfv(GL_LIGHT0, GL_POSITION, lights[0].position);
			glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, lights[0].constantAttenuation);
			glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, lights[0].linearAttenuation);
			glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, lights[0].quadraticAttenuation);
		}
		else if (lights[0].type == 1) {
			glLightfv(GL_LIGHT0, GL_AMBIENT, lights[0].ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lights[0].diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, lights[0].specular);
			glLightfv(GL_LIGHT0, GL_POSITION, lights[0].position);
			glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, lights[0].constantAttenuation);
			glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, lights[0].linearAttenuation);
			glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, lights[0].quadraticAttenuation);
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lights[0].spotCutoff);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lights[0].direction);
			glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, lights[0].spotExponent);

		}
		glEnable(GL_LIGHT0);
		break;
	case 1:
		if (lights[1].type == 0) {
			glLightfv(GL_LIGHT1, GL_AMBIENT, lights[1].ambient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, lights[1].diffuse);
			glLightfv(GL_LIGHT1, GL_SPECULAR, lights[1].specular);
			glLightfv(GL_LIGHT1, GL_POSITION, lights[1].position);
			glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, lights[1].constantAttenuation);
			glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, lights[1].linearAttenuation);
			glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, lights[1].quadraticAttenuation);
		}
		else if (lights[1].type == 1) {
			glLightfv(GL_LIGHT1, GL_AMBIENT, lights[1].ambient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, lights[1].diffuse);
			glLightfv(GL_LIGHT1, GL_SPECULAR, lights[1].specular);
			glLightfv(GL_LIGHT1, GL_POSITION, lights[1].position);
			glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, lights[1].constantAttenuation);
			glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, lights[1].linearAttenuation);
			glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, lights[1].quadraticAttenuation);
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, lights[1].spotCutoff);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lights[1].direction);
			glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, lights[1].spotExponent);

		}
		glEnable(GL_LIGHT1);
		lights[1].draw();
		break;
	case 2:
		if (lights[2].type == 0) {
			glLightfv(GL_LIGHT2, GL_AMBIENT, lights[2].ambient);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, lights[2].diffuse);
			glLightfv(GL_LIGHT2, GL_SPECULAR, lights[2].specular);
			glLightfv(GL_LIGHT2, GL_POSITION, lights[2].position);
			glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, lights[2].constantAttenuation);
			glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, lights[2].linearAttenuation);
			glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, lights[2].quadraticAttenuation);
		}
		else if (lights[2].type == 1) {
			glLightfv(GL_LIGHT2, GL_AMBIENT, lights[2].ambient);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, lights[2].diffuse);
			glLightfv(GL_LIGHT2, GL_SPECULAR, lights[2].specular);
			glLightfv(GL_LIGHT2, GL_POSITION, lights[2].position);
			glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, lights[2].constantAttenuation);
			glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, lights[2].linearAttenuation);
			glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, lights[2].quadraticAttenuation);
			glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lights[2].spotCutoff);
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lights[2].direction);
			glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, lights[2].spotExponent);

		}
		glEnable(GL_LIGHT2);
		lights[2].draw();
		break;

	case 3:
		if (lights[3].type == 0) {
			glLightfv(GL_LIGHT3, GL_AMBIENT, lights[3].ambient);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, lights[3].diffuse);
			glLightfv(GL_LIGHT3, GL_SPECULAR, lights[3].specular);
			glLightfv(GL_LIGHT3, GL_POSITION, lights[3].position);
			glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, lights[3].constantAttenuation);
			glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, lights[3].linearAttenuation);
			glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, lights[3].quadraticAttenuation);
		}
		else if (lights[3].type == 1) {
			glLightfv(GL_LIGHT3, GL_AMBIENT, lights[3].ambient);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, lights[3].diffuse);
			glLightfv(GL_LIGHT3, GL_SPECULAR, lights[3].specular);
			glLightfv(GL_LIGHT3, GL_POSITION, lights[3].position);
			glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, lights[3].constantAttenuation);
			glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, lights[3].linearAttenuation);
			glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, lights[3].quadraticAttenuation);
			glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, lights[3].spotCutoff);
			glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lights[3].direction);
			glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, lights[3].spotExponent);

		}
		glEnable(GL_LIGHT3);
		lights[3].draw();
		break;
	case 4:
		if (lights[4].type == 0) {
			glLightfv(GL_LIGHT4, GL_AMBIENT, lights[4].ambient);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, lights[4].diffuse);
			glLightfv(GL_LIGHT4, GL_SPECULAR, lights[4].specular);
			glLightfv(GL_LIGHT4, GL_POSITION, lights[4].position);
			glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, lights[4].constantAttenuation);
			glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, lights[4].linearAttenuation);
			glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, lights[4].quadraticAttenuation);
		}
		else if (lights[4].type == 1) {
			glLightfv(GL_LIGHT4, GL_AMBIENT, lights[4].ambient);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, lights[4].diffuse);
			glLightfv(GL_LIGHT4, GL_SPECULAR, lights[4].specular);
			glLightfv(GL_LIGHT4, GL_POSITION, lights[4].position);
			glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, lights[4].constantAttenuation);
			glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, lights[4].linearAttenuation);
			glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, lights[4].quadraticAttenuation);
			glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, lights[4].spotCutoff);
			glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lights[4].direction);
			glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, lights[4].spotExponent);

		}
		glEnable(GL_LIGHT4);
		lights[4].draw();
		break;
	case 5:
		if (lights[5].type == 0) {
			glLightfv(GL_LIGHT5, GL_AMBIENT, lights[5].ambient);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, lights[5].diffuse);
			glLightfv(GL_LIGHT5, GL_SPECULAR, lights[5].specular);
			glLightfv(GL_LIGHT5, GL_POSITION, lights[5].position);
			glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, lights[5].constantAttenuation);
			glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, lights[5].linearAttenuation);
			glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, lights[5].quadraticAttenuation);
		}
		else if (lights[5].type == 1) {
			glLightfv(GL_LIGHT5, GL_AMBIENT, lights[5].ambient);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, lights[5].diffuse);
			glLightfv(GL_LIGHT5, GL_SPECULAR, lights[5].specular);
			glLightfv(GL_LIGHT5, GL_POSITION, lights[5].position);
			glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, lights[5].constantAttenuation);
			glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, lights[5].linearAttenuation);
			glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, lights[5].quadraticAttenuation);
			glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, lights[5].spotCutoff);
			glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, lights[5].direction);
			glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, lights[5].spotExponent);

		}
		glEnable(GL_LIGHT5);
		lights[5].draw();
		break;
	case 6:
		if (lights[6].type == 0) {
			glLightfv(GL_LIGHT6, GL_AMBIENT, lights[6].ambient);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, lights[6].diffuse);
			glLightfv(GL_LIGHT6, GL_SPECULAR, lights[6].specular);
			glLightfv(GL_LIGHT6, GL_POSITION, lights[6].position);
			glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, lights[6].constantAttenuation);
			glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, lights[6].linearAttenuation);
			glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, lights[6].quadraticAttenuation);
		}
		else if (lights[6].type == 1) {
			glLightfv(GL_LIGHT6, GL_AMBIENT, lights[6].ambient);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, lights[6].diffuse);
			glLightfv(GL_LIGHT6, GL_SPECULAR, lights[6].specular);
			glLightfv(GL_LIGHT6, GL_POSITION, lights[6].position);
			glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, lights[6].constantAttenuation);
			glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, lights[6].linearAttenuation);
			glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, lights[6].quadraticAttenuation);
			glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, lights[6].spotCutoff);
			glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, lights[6].direction);
			glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, lights[6].spotExponent);

		}
		glEnable(GL_LIGHT6);
		lights[6].draw();
		break;
	}
}

void light::turnOff(int i) {
	switch (i) {
	case 0:
		glDisable(GL_LIGHT0);
		break;
	case 1:
		glDisable(GL_LIGHT1);
		break;
	case 2:
		glDisable(GL_LIGHT2);
		break;

	case 3:
		glDisable(GL_LIGHT3);
		break;
	case 4:
		glDisable(GL_LIGHT4);
		break;
	case 5:
		glDisable(GL_LIGHT5);
		break;
	case 6:
		glDisable(GL_LIGHT6);
		break;
	}
}