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
	float** getBoundingBox();
	void loseLife();
	void resetLifes();
	void collide(DynamicObject* frog);
	int getLifes();
	int getPoints();

};

#endif