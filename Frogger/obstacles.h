#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"


#include "car.h"

class Obstacles{

private:
	float level;
	float startingPosX[3];
	std::vector<Car> numEnemies;

public:
	Obstacles();
	~Obstacles();

	void setStartingPosX(){
		startingPosX[0] = 5.0f;
		startingPosX[1] = 8.0f;
		startingPosX[2] = 11.0f;
	}

	void setLevel(float lvl);
	void addEnemy();
	void updatePosition();
	void render(VSShaderLib shader);

};

#endif