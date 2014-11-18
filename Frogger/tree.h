#ifndef TREE_H
#define TREE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#include "staticObject.h"
#include "constants.h"
#include "surface.h"

class Tree : public StaticObject{

private:

	Surface *billboard;
	
	float angle;
	float vector[3];
	float auxVector[3];
	float vectorOrientation[3];

public:

	Tree(float x, float y, float z);
	~Tree();

	void setupObjects();
	void render(VSShaderLib shader);
	void updateRotation(float* frogPos);
};

#endif