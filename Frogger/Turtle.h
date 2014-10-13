#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"
#ifndef Turtle_H
#define Turtle_H


class Turtle{

private:

	float actualPosition[3];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[7];
	bool side;


public:
	Turtle(bool side);
	~Turtle();

	float* getActualPostion();
	void setupObjects();
	void render();
	void move();
};

#endif