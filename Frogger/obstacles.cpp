#include "obstacles.h"

Obstacles::Obstacles(){
	levelRoad = 1;
	levelWater = 1;
	setStartingPosCar();
	setStartingPosWater();
}
Obstacles::~Obstacles(){};

/*
Obstacles::Obstacles(char* enemy){
	
	if (!strcmp(enemy, "car")){
		numEnemies.push_back(new Car(true, 5.0f, 0.0f, 0.0f));
	}
	else if (!strcmp(enemy, "turtle")){
		numEnemies.push_back(new Turtle(true, 20.0f, 0.0f, 0.0));
	}
	else if (!strcmp(enemy, "wood")){
		numEnemies.push_back(new Wood(true, 23.0f, 0.0f, 0.0));
	}
};
*/

//set speed of game
void Obstacles::setLevel(float road, float water){
	levelRoad = road;
	levelWater = water;
}

//adds enemy
void Obstacles::addEnemy(char* enemy){
	int v;
	float xStart;
	v = rand() % 3;
	if (!strcmp(enemy, "car")){
		xStart = startingPosCar[v];
		numEnemies.push_back(new Car(true, xStart, 0.0f, 0.0));
	}
	if (!strcmp(enemy, "turtle")){
		xStart = startingPosWater[v];
		numEnemies.push_back(new Turtle(false, 23.0f, 0.0f, 100.0));
	}
	if (!strcmp(enemy, "wood")){
		xStart = startingPosWater[v];
		numEnemies.push_back(new Wood(true, xStart, 0.0f, 0.0));
	}
}

//moves every enemy to the right, should be called every display
void Obstacles::updatePosition(){
	for (int i = 0; i < numEnemies.size(); i++)
		if (!strcmp(numEnemies[i]->toString(), "car")){
			numEnemies[i]->move(levelRoad);
		}
		else numEnemies[i]->move(levelWater);
	
}

//render enemies
void Obstacles::render(VSShaderLib shader) {
	for (int i = 0; i < numEnemies.size(); i++)
		numEnemies[i]->render(shader);
}

void Obstacles::destroyObstacles(){
	float* actual;
	for (int i = 0; i < numEnemies.size(); i++){
		actual = numEnemies[i]->getActualPosition();
		if (actual[2]>100||actual[2]<0)
			numEnemies.erase(numEnemies.begin() + i);
	}
}