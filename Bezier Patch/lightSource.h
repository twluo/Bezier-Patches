#ifndef _LIGHTSOURCE_H_
#define _LIGHTSOURCE_H_

#include "Matrix4.h"
#include "Vector3.h"
class lightSource
{
private:
	int pos;
public:
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
	float direction[3];
	double constantAttenuation;
	double linearAttenuation;
	double quadraticAttenuation;
	double spotCutoff;
	double spotExponent;
	int type;
	lightSource();
	~lightSource();
	lightSource(int);
	void draw();
};

#endif