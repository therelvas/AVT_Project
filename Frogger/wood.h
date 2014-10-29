#ifndef WOOD_H
#define WOOD_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "dynamicObject.h"

class Wood : public DynamicObject {

private:

	VSResSurfRevLib *vsres;

public:

	Wood(float x, float y, float z);
	~Wood();

	void setupObjects();
	void render(VSShaderLib shader);

	void move(float x, float y, float z, float speed);
	
	float** getBoundingBox();
	void collide(DynamicObject* dynamicObject);
};

#endif