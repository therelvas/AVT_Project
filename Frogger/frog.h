#ifndef FROG_H
#define FROG_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#define DISPLACEMENT 0.2

class Frog{

private:

	int lifes;
	float actualPosition[3];
	float lastPosition[3];
	float color[4];
	bool initialized;

	VSMathLib *vsml;
	VSResSurfRevLib *vsres[2];


public:
	Frog();
	~Frog();

	void setupObjects();
	void render(VSShaderLib shader);

	float* getActualPostion();

	void moveToFront();
	void moveToBack();
	void moveToLeft();
	void moveToRight();
};

#endif