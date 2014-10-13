#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"
#ifndef ENEMY_H
#define ENEMY_H

#include "Cube.h"

class Enemy{

private:

	float actualPosition[3];
	Cube* cube[2];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[6];
	bool side;


public:
	Enemy(bool side);
	~Enemy();

	float* getActualPostion();
	float* getLastPosition();

	void updatePosition(float x, float y){
		actualPosition[0] = x;
		actualPosition[1] = y;
	}

	void setupObjects();
	void render();

	void move();
};

#endif