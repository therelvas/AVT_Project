#ifndef FROG_H
#define FROG_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

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

	float* getActualPostion();
	float* getLastPosition();

	void updatePosition(float x, float y){
		actualPosition[0] = x;
		actualPosition[1] = y;
		lastPosition[0] = actualPosition[0];
		lastPosition[1] = actualPosition[1];
		lastPosition[2] = actualPosition[2];
		lastPosition[3] = actualPosition[3];
	}

	void setupObjects();
	void render();

	void moveToFront();
	void moveToBack();
	void moveToLeft();
	void moveToRight();
};

#endif