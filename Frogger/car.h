#ifndef CAR_H
#define CAR_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"


#include "Cube.h"
#include "enemy.h"

class Car:public Enemy{

private:

	float actualPosition[3];
	Cube* cube[2];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[6];
	bool side;


public:

	Car(bool side, float x, float y, float z);
	~Car();

	virtual char* toString(){ return "car"; }
	virtual float* getActualPosition();
	virtual void setupObjects();
	virtual void render(VSShaderLib shader);
	virtual void move(float lvl);
};

#endif