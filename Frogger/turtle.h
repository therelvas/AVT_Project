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

	void setupObjects();
	void render(VSShaderLib shader);

	void move(float x, float y, float z, float speed);

	float** getBoundingBox();
	void collide(DynamicObject* dynamicObject);
};

#endif