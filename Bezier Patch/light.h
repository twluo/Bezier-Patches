#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <vector>
#include "lightSource.h"
class light
{
public:
	std::vector < lightSource > lights ;
	void setType(int, int);
	void setAmbient(int, float, float, float, float);
	void setDiffuse(int,float, float, float, float);
	void setSpecular(int,float, float, float, float);
	void setPosition(int,float, float, float, float);
	void setDirection(int,float, float, float);
	void setAttenuation(int,double,double, double);
	void setSpotCutoff(int,double);
	void setSpotExponent(int,double);
	light();
	~light();
	void turnOn(int);
	void turnOff(int);
};

#endif