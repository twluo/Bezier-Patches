#include "material.h"
#include "GL/glut.h"

material::material()
{
	for (int i = 0; i < 4; i++) {
		if (i < 3)
			color[i] = 0;
		ambient[i] = 0;
		diffuse[i] = 0;
		specular[i] = 0;
		emission[i] = 0;
	}
	shininess[0] = 0;
}


material::~material()
{
}

void material::setAmbient(float a, float b, float c, float d){
	ambient[0] = a;
	ambient[1] = b;
	ambient[2] = c; 
	ambient[3] = d;
}
void material::setDiffuse(float a, float b, float c, float d){
	diffuse[0] = a;
	diffuse[1] = b;
	diffuse[2] = c;
	diffuse[3] = d;
}
void material::setSpecular(float a, float b, float c, float d){
	specular[0] = a;
	specular[1] = b;
	specular[2] = c;
	specular[3] = d;
}
void material::setShininess(float a){
	shininess[0] = a;
}
void material::setEmission(float a, float b, float c, float d){
	emission[0] = a;
	emission[1] = b;
	emission[2] = c;
	emission[3] = d;
}
void material::setColor(float a, float b, float c) {
	color[0] = a;
	color[1] = b;
	color[2] = c;
}
void material::setProperties() {

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
}