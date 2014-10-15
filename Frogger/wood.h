#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"
#ifndef Wood_H
#define Wood_H

#include "enemy.h"

class Wood:public Enemy{

private:

	float actualPosition[3];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[3];
	bool side;


public:
	Wood(bool side, float x, float y, float z);
	~Wood();

	virtual char* toString(){ return "wood"; }
	virtual float* getActualPosition();
	virtual void setupObjects();
	virtual void render(VSShaderLib shader);
	virtual void move(float lvl);
};

#endif