#include "frog.h"

Frog::Frog(float x, float y, float z) : DynamicObject(x, y, z) {

	for (int i = 0; i < 4; i++) {
		vsres[i] = new VSResSurfRevLib();
	}
	
	lives = 5;
	gamePoints = 0;

	setupObjects();
}

Frog::~Frog(){}

void Frog::setupObjects() {
	
	float body_amb[] = { 0.05f, 0.05f, 0.0f, 1.0f };
	float body_diff[] = { 0.1f, 0.55f, 0.1f, 1.0f };
	float body_spec[] = { 0.35f, 0.65f, 0.45f, 1.0f };
	float body_shininess[] = { 0.25f };

	float eyes_diff[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//Head
	vsres[0]->createSphere(0.5f, 40);
	vsres[0]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[0]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[0]->setColor(VSResourceLib::SHININESS, body_shininess);

	//Eyes
	vsres[1]->createSphere(0.2f, 40);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, eyes_diff);
	vsres[1]->setColor(VSResourceLib::SPECULAR, eyes_diff);

	//Body
	vsres[2]->createCylinder(1.0f, 0.5f, 40);
	vsres[2]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[2]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[2]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[3]->createSphere(0.5f, 40);
	vsres[3]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[3]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[3]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[3]->setColor(VSResourceLib::SHININESS, body_shininess);
}

void Frog::render(VSShaderLib shader) {
	
	vsml->loadIdentity(VSMathLib::MODEL);

	//Head
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.5f, position[1] + 0.5f, position[2]);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Eyes
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.8f, position[1] + 0.8f, position[2] + 0.2f);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.8f, position[1] + 0.8f, position[2] - 0.2f);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Body
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2]);
	vsml->rotate(90.0f, 1.0f, 0.0f, 0.0f);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2] + 0.5f);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2] - 0.5f);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Frog::move(float x, float y, float z, float speed) {
	
	if (!(position[0] + x*speed <= 32 && position[0] + x*speed >= 0))
		return;
	if (!(position[2] + z*speed <= 100 && position[2] + z*speed >= 0))
		return;

	position[0] += x * speed;
	position[1] += y * speed;
	position[2] += z * speed;
}

float** Frog::getBoundingBox(){

	float** boundingBox = 0;

	boundingBox = new float*[2];
	boundingBox[0] = new float[3];
	boundingBox[1] = new float[3];
	
	boundingBox[0][0] = position[0] + 1.2f;
	boundingBox[0][1] = position[1];
	boundingBox[0][2] = position[2] - 1.0f;

	boundingBox[1][0] = position[0] - 1.2f;
	boundingBox[1][1] = position[1];
	boundingBox[1][2] = position[2] + 1.0f;

	return boundingBox;
}

void Frog::resetLifes() {

	lives = 5;
	gamePoints = 0;
}

void Frog::collide(DynamicObject* dynamicObject) {

	if (collided){
		collided = false;
		return;
	}
	else {

		if (position[0] > 18 && position[0] < 28){
			loseLife();
			dynamicObject->resetPosition();
		}
		if (position[0] > 30){
			gamePoints += 10;
			dynamicObject->resetPosition();
		}
	}
}

int Frog::getPoints(){
	
	return gamePoints;
}
