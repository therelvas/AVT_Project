#ifndef TURTLE_H
#define TURTLE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

#include "enemy.h"

class Turtle :public Enemy{

private:

	float actualPosition[3];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[7];
	bool side;

public:

	Turtle(bool side, float x, float y, float z);
	~Turtle();

	virtual char* toString(){ return "turtle"; }
	virtual float* getActualPosition();
	virtual void setupObjects();
	virtual void render(VSShaderLib shader);
	virtual void move(float lvl);
};

#endif