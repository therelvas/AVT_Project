#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#include "constants.h"

class GameObject {

protected:

	float position[3];
	float initialPosition[3];
	VSMathLib *vsml;

public:

	GameObject(float x, float y, float z);
	~GameObject();

	float* getPosition();
	void resetPosition();
	bool isInitialPos();

	virtual void setupObjects();
	virtual void render(VSShaderLib shader);
};

#endif