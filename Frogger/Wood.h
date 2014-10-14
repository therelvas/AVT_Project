#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"
#ifndef Wood_H
#define Wood_H


class Wood{

private:

	float actualPosition[3];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[3];
	bool side;


public:
	Wood(bool side, float x, float y, float z);
	~Wood();

	float* getActualPostion();
	void setupObjects();
	void render(VSShaderLib shader);
	void move();
};

#endif