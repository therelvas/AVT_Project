#include "Frog.h"

Frog::Frog(float x, float y, float z) : DynamicObject(x, y, z) {

	for (int i = 0; i < 6; i++){
		vsres[i] = new VSResSurfRevLib();
	}
	lifes = 5;
	Frog::gamePoints = 0;

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
	vsres[1]->createSphere(0.5f, 40);
	vsres[1]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[1]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[1]->setColor(VSResourceLib::SHININESS, body_shininess);

	//Eyes
	vsres[2]->createSphere(0.2f, 40);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, eyes_diff);
	vsres[2]->setColor(VSResourceLib::SPECULAR, eyes_diff);

	vsres[3]->createSphere(0.2f, 40);
	vsres[3]->setColor(VSResourceLib::DIFFUSE, eyes_diff);
	vsres[3]->setColor(VSResourceLib::SPECULAR, eyes_diff);

	//Body
	vsres[0]->createCylinder(1.0f, 0.5f, 40);
	vsres[0]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[0]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[0]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[4]->createSphere(0.5f, 40);
	vsres[4]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[4]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[4]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[4]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[5]->createSphere(0.5f, 40);
	vsres[5]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[5]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[5]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[5]->setColor(VSResourceLib::SHININESS, body_shininess);
}

void Frog::render(VSShaderLib shader) {
	
	//Head
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.5f, position[1] + 0.5f, position[2]);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Eyes
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.8f, position[1] + 0.8f, position[2] + 0.2f);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.8f, position[1] + 0.8f, position[2] - 0.2f);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Body
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2]);
	vsml->rotate(90.0f, 1.0f, 0.0f, 0.0f);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2] + 0.5f);
	vsres[4]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2] - 0.5f);
	vsres[5]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

float** Frog::getBoundingBox(){
	float** boundingBox = 0;
	boundingBox = new float*[2];
	boundingBox[0] = new float[3];
	boundingBox[1] = new float[3];
	boundingBox[0][0] = position[0] + 1.2f;
	boundingBox[0][1] = position[1];
	boundingBox[0][2] = position[2] - 1.0f;

	boundingBox[1][0] = position[0] - 1.2;
	boundingBox[1][1] = position[1];
	boundingBox[1][2] = position[2] + 1.0f;

	return boundingBox;
}

void Frog::loseLife(){
	lifes--;
}

void Frog::resetLifes(){
	lifes = 5;
	gamePoints = 0;
}

void Frog::collide(DynamicObject* frog){
	if (Frog::collided){
		Frog::collided = false;
		return;
	}
	else{
		if (position[0] > 18 && position[0] < 28){
			loseLife();
			frog->resetPosition();
		}
		if (position[0] > 30){
			Frog::gamePoints += 10;
			frog->resetPosition();
		}
	}
}

int Frog::getLifes(){
	return lifes;
}

int Frog::getPoints(){
	return Frog::gamePoints;
}
