#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "enemy.h"
#include "car.h"
#include "turtle.h"
#include "wood.h"

class Obstacles{

private:
	float levelRoad;
	float levelWater;
	float startingPosCar[3], startingPosWater[3];
	std::vector<Enemy*> numEnemies;

public:
	Obstacles();
	//Obstacles(char* enemy);
	~Obstacles();

	void setStartingPosCar(){
		startingPosCar[0] = 5.0f;
		startingPosCar[1] = 8.0f;
		startingPosCar[2] = 11.0f;
	}
	void setStartingPosWater(){
		startingPosWater[0] = 20.0f;
		startingPosWater[1] = 26.0f;
		startingPosWater[2] = 26.0f;
	}

	void setLevel(float road, float water);
	void addEnemy(char* enemy);
	void updatePosition();
	void render(VSShaderLib shader);
	void destroyObstacles();
};

#endif