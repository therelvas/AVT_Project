#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#include "gameObject.h"

class DynamicObject : public GameObject {

public:

	DynamicObject(float x, float y, float z);
	~DynamicObject();

	virtual void setupObjects();
	virtual void render(VSShaderLib shader);

	virtual void move(float x, float y, float z, float speed);
};

#endif 