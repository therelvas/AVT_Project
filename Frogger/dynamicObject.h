#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#include "gameObject.h"

class DynamicObject : public GameObject {
protected:
	int lifes;

public:
	bool collided = false;

	DynamicObject(float x, float y, float z);
	~DynamicObject();

	virtual void setupObjects();
	virtual void render(VSShaderLib shader);

	virtual void move(float x, float y, float z, float speed);
	virtual void moveFrog(float x, float y, float z, float speed);
	virtual void collide(DynamicObject* frog);
	virtual float** getBoundingBox();
	virtual void loseLife();
	virtual int getLifes();
	virtual void resetLifes();
};

#endif 