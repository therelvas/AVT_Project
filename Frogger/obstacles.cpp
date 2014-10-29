#include "obstacles.h"

Obstacles::Obstacles(Frog* frog) {

	Obstacles::frog = frog;

	level = 1;
	setStartingPositions();
	generateEnemies();
}

Obstacles::~Obstacles(){};

//Set speed of game
void Obstacles::setLevel(float level) {

	Obstacles::level = level;
}

void Obstacles::setStartingPositions(){
	
	startingPosCarX[0] = STARTING_POS_CAR_X1;
	startingPosCarX[1] = STARTING_POS_CAR_X2;
	startingPosCarX[2] = STARTING_POS_CAR_X3;

	startingPosWood[0] = STARTING_POS_WOOD_X1;
	startingPosWood[1] = STARTING_POS_WOOD_X2;
	startingPosWood[2] = STARTING_POS_WOOD_X3;

	startingPosTurtle[0] = STARTING_POS_TURTLE_X1;	
}

//Add enemies randomly
void Obstacles::generateEnemies() {
	
	int size = enemies.size();

	while (size < MAX_ENEMIES) {

		int type = rand() % 25;
		int pos = rand() % 3;
		enemies.push_back(new Wood(startingPosWood[pos], -1.0f, 0.0f));

		//Car
		if (type < 10) {
			enemies.push_back(new Car(startingPosCarX[pos], 0.0f, 0.0f));
		}
		//Turtle
		else if (type >= 10 && type <= 15) {
			enemies.push_back(new Turtle(startingPosTurtle[0], 0.0f, 100.0f));
		}
		//Wood
		else if (type > 15) {
			enemies.push_back(new Wood(startingPosWood[pos], -1.0f, 0.0f));
		}
		size = enemies.size();
	}
}

//Moves every enemy, should be called every display
void Obstacles::updatePosition() {

	int size = enemies.size();
	int move;

	for (int i = 0; i < size; i++) {
		move = rand() % 150;
		enemies[i]->collide(frog);

		if (enemies[i]->isInitialPos() && move == 1) {
			enemies[i]->move(0.0f, 0.0f, 0.0f, level); //No parameters given because they control themselves	
		}
		else if (!enemies[i]->isInitialPos()) {
			enemies[i]->move(0.0f, 0.0f, 0.0f, level);
		}
	} 
	frog->collide(frog); 
}

//Render enemies
void Obstacles::render(VSShaderLib shader) {

	int size = enemies.size();
	
	for (int i = 0; i < size; i++) {
		if (!enemies[i]->isInitialPos())
			enemies[i]->render(shader);
	}
}

void Obstacles::destroyObstacles() {
	
	float actual;
	int size = enemies.size();

	for (int i = 0; i < size; i++) {
		actual = enemies[i]->getPosition()[2];
		if (actual > SCALE_FACTOR_Z || actual < 0.0f) {
			enemies[i]->resetPosition();
		}
	}
}