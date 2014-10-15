#ifndef ENEMY_H
#define ENEMY_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

class Enemy{

public:

	Enemy(){};
	~Enemy(){};

	virtual char* toString() = 0;
	virtual float* getActualPosition() = 0;
	virtual void setupObjects() = 0;
	virtual void render(VSShaderLib shader) = 0;
	virtual void move(float lvl) = 0;
};

#endif