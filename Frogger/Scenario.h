#ifndef SCENARIO_H
#define SCENARIO_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "Cube.h"

#define BORDER2_X 14
#define BORDER3_X 28
#define STREET_X 4
#define WATER_X 18
#define SCALE_FACTOR_Z 100
#define BORDER_SCALE_FACTOR_X 4
#define OTHER_SCALE_FACTOR_X 10


class Scenario{

private:

	VSMathLib *vsml;
	VSResSurfRevLib *vsres[5];
	Cube* cube[6];
	float defaultPosition[3];


public:
	Scenario();
	~Scenario();

	void setupObjects();
	void render();
};

#endif