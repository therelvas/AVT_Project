#ifndef FROG_H
#define FROG_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

class Frog{

private:

	int lifes;
	float actualPosition[3];
	float color[4];
	bool initialized;

	VSMathLib *vsml;
	VSResSurfRevLib *vsres[2];


public:
	Frog(float x, float y, float z);
	~Frog();

	float* getActualPostion();

	void setupObjects();
	void render(VSShaderLib shader);

	void moveToFront();
	void moveToBack();
	void moveToLeft();
	void moveToRight();
};

#endif