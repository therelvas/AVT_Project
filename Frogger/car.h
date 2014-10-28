#ifndef CAR_H
#define CAR_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "Cube.h"
#include "dynamicObject.h"

class Car : public DynamicObject {

private:

	Cube* cube[2];
	VSResSurfRevLib *vsres[4];

public:

	Car(float x, float y, float z);
	~Car();

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