#ifndef TURTLE_H
#define TURTLE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

class Turtle{

private:

	float actualPosition[3];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[7];
	bool side;

public:

	Turtle(bool side, float x, float y, float z);
	~Turtle();

	float* getActualPosition();
	void setupObjects();
	void render(VSShaderLib shader);
	void move();
};

#endif