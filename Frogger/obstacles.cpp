#include "obstacles.h"

Obstacles::Obstacles(){
	level = 1;
	setStartingPosX();
	numEnemies.push_back(Car(true, 5.0f, 0.0f, 0.0f));
};

Obstacles::~Obstacles(){};

//set speed of game
void Obstacles::setLevel(float lvl){
	level = lvl;
}

//adds enemy
void Obstacles::addEnemy(){
	int v;
	float xStart;
	v = rand() % 3;
	xStart = startingPosX[v];

	numEnemies.push_back(Car(true, xStart, 0.0f, 0.0));
}

//moves every enemy to the right, should be called every display
void Obstacles::updatePosition(){
	for (int i = 0; i < numEnemies.size(); i++)
		numEnemies[i].move(level);
}

//render enemies
void Obstacles::render(VSShaderLib shader) {
	for (int i = 0; i < numEnemies.size(); i++)
		numEnemies[i].render(shader);
}

void Obstacles::destroyObstacles(){
	float* actual;
	for (int i = 0; i < numEnemies.size(); i++){
		actual = numEnemies[i].getActualPostion();
		if (actual[2]>100)
			numEnemies.erase(numEnemies.begin() + i);
	}
}