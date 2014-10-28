#ifndef TURTLE_H
#define TURTLE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#include "dynamicObject.h"

class Turtle : public DynamicObject {

private:

	VSResSurfRevLib *vsres[7];

public:

	Turtle(float x, float y, float z);
	~Turtle();

	virtual void setupObjects();
	virtual void render(VSShaderLib shader);

	virtual void move(float x, float y, float z, float speed);
	virtual float** getBoundingBox();
	virtual void collide(DynamicObject* frog);
	virtual void loseLife();
	virtual int getLifes();
	virtual void resetLifes();
};

#endif