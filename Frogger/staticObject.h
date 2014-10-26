#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#include "gameObject.h"

class StaticObject: public GameObject {

public:

	StaticObject(float x, float y, float z);
	~StaticObject();

	virtual void setupObjects();
	virtual void render(VSShaderLib shader);
};

#endif 