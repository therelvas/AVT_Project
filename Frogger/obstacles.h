#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "constants.h"

#include "car.h"
#include "turtle.h"
#include "wood.h"

class Obstacles {

private:

	int readyRand;

	float level;
	float startingPosCarX[3], startingPosCarZ[3];
	float startingPosWood[3], startingPosTurtle[1];

	std::vector<DynamicObject*> enemies;

	void setStartingPositions();	

public:

	Obstacles();
	~Obstacles();

	void setLevel(float level);	
	
	void generateEnemies();
	void updatePosition();
	void destroyObstacles();
	void render(VSShaderLib shader);	
};

#endif