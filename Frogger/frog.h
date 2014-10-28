#ifndef FROG_H
#define FROG_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "dynamicObject.h"

class Frog : public DynamicObject {

private:
	VSResSurfRevLib *vsres[2];

public:

	Frog(float x, float y, float z);
	~Frog();

	virtual void setupObjects();
	virtual void render(VSShaderLib shader);
	virtual float** getBoundingBox();
	virtual void loseLife();
	virtual void resetLifes();
	virtual void collide(DynamicObject* frog);
	virtual int getLifes();

};

#endif