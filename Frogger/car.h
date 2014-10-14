#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"
#ifndef Car_H
#define Car_H

#include "Cube.h"

class Car{

private:

	float actualPosition[3];
	Cube* cube[2];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[6];
	bool side;


public:
	Car(bool side, float x, float y, float z);
	~Car();

	float* getActualPostion();

	void setupObjects();
	void render(VSShaderLib shader);

	void move();
};

#endif