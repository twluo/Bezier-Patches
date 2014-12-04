#pragma once
class material
{
public:
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess[1];
	float emission[4];
	float color[3];
	void setAmbient(float, float, float, float);
	void setDiffuse(float, float, float, float);
	void setSpecular(float, float, float, float);
	void setShininess(float);
	void setEmission(float, float, float, float);
	void setColor(float, float, float);
	material();
	~material();
	void setProperties();
};

