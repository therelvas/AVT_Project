#ifndef FROG_H
#define FROG_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#include "dynamicObject.h"

class Frog : public DynamicObject {

private:

	int gamePoints;
	VSResSurfRevLib *vsres[2];

public:

	Frog(float x, float y, float z);
	~Frog();

	void setupObjects();
	void render(VSShaderLib shader);

	void move(float x, float y, float z, float speed);

	float** getBoundingBox();
	void collide(DynamicObject* dynamicObject);

	int getPoints();
	void resetLifes();
};

#endif