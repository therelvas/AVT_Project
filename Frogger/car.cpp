#include "Car.h"

Car::Car(float x, float y, float z) : DynamicObject(x, y, z) {

	for (int i = 0; i < 6; i++) {
		vsres[i] = new VSResSurfRevLib();
	}
	cube[0] = new Cube();
	cube[1] = new Cube();

	setupObjects();
}

Car::~Car(){}

void Car::setupObjects() {

	float body_amb[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
	float body_diff[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
	float body_spec[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
	float body_shininess[] = { 76.8f };

	float tires_diff[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	//Body
	cube[0]->setColor(VSResourceLib::AMBIENT, body_amb);
	cube[0]->setColor(VSResourceLib::DIFFUSE, body_diff);
	cube[0]->setColor(VSResourceLib::SPECULAR, body_spec);
	cube[0]->setColor(VSResourceLib::SHININESS, body_shininess);
	
	cube[1]->setColor(VSResourceLib::AMBIENT, body_amb);
	cube[1]->setColor(VSResourceLib::DIFFUSE, body_diff);
	cube[1]->setColor(VSResourceLib::SPECULAR, body_spec);
	cube[1]->setColor(VSResourceLib::SHININESS, body_shininess);

	//Tires
	vsres[0]->createSphere(0.5f, 30);
	vsres[0]->setColor(VSResourceLib::AMBIENT, tires_diff);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, tires_diff);
	vsres[0]->setColor(VSResourceLib::SPECULAR, tires_diff);
	vsres[0]->setColor(VSResourceLib::SHININESS, tires_diff);

	vsres[1]->createSphere(0.5f, 30);
	vsres[1]->setColor(VSResourceLib::AMBIENT, tires_diff);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, tires_diff);
	vsres[1]->setColor(VSResourceLib::SPECULAR, tires_diff);
	vsres[1]->setColor(VSResourceLib::SHININESS, tires_diff);

	vsres[2]->createSphere(0.5f, 30);
	vsres[2]->setColor(VSResourceLib::AMBIENT, tires_diff);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, tires_diff);
	vsres[2]->setColor(VSResourceLib::SPECULAR, tires_diff);
	vsres[2]->setColor(VSResourceLib::SHININESS, tires_diff);

	vsres[3]->createSphere(0.5f, 30);
	vsres[3]->setColor(VSResourceLib::AMBIENT, tires_diff);
	vsres[3]->setColor(VSResourceLib::DIFFUSE, tires_diff);
	vsres[3]->setColor(VSResourceLib::SPECULAR, tires_diff);
	vsres[3]->setColor(VSResourceLib::SHININESS, tires_diff);

	vsres[4]->createSphere(0.5f, 30);
	vsres[4]->setColor(VSResourceLib::AMBIENT, tires_diff);
	vsres[4]->setColor(VSResourceLib::DIFFUSE, tires_diff);
	vsres[4]->setColor(VSResourceLib::SPECULAR, tires_diff);
	vsres[4]->setColor(VSResourceLib::SHININESS, tires_diff);
}

void Car::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);

	//Body
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2]);
	vsml->scale(2.0f, 1.0f, 5.0f);
	cube[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1] + 1.0f, position[2] + 1.0f);
	vsml->scale(2.0f, 1.0f, 3.0f);
	cube[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Tires
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.15f, position[1], position[2] + 1.0f);
	vsml->scale(0.5f, 1.0f, 1.0f);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.15f, position[1], position[2] + 4.0f);
	vsml->scale(0.5f, 1.0f, 1.0f);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 1.85f, position[1], position[2] + 4.0f);
	vsml->scale(0.5f, 1.0f, 1.0f);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 1.85f, position[1], position[2] + 1.0f);
	vsml->scale(0.5f, 1.0f, 1.0f);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Car::move(float x, float y, float z, float speed) {

	position[0] += 0.0f * speed;
	position[1] += 0.0f * speed;
	position[2] += 0.2f * speed;
}

float** Car::getBoundingBox(){
	float** boundingBox = 0;
	boundingBox = new float*[2];
	boundingBox[0] = new float[3];
	boundingBox[1] = new float[3];

	boundingBox[0][0] = position[0] + 1.0f;
	boundingBox[0][1] = 0;
	boundingBox[0][2] = position[2] - 2.5f;


	boundingBox[1][0] = position[0] - 1;
	boundingBox[1][1] = 0;
	boundingBox[1][2] = position[2] + 2.5f;

	return boundingBox;
}

void Car::collide(DynamicObject* frog){
	if (frog->getBoundingBox()[0][0] >= getBoundingBox()[1][0] && frog->getBoundingBox()[0][0] <= getBoundingBox()[0][0]
		&&
		frog->getBoundingBox()[0][2] <= getBoundingBox()[1][2] && frog->getBoundingBox()[0][2] >= getBoundingBox()[0][2])
		frog->resetPosition();
	else if (frog->getBoundingBox()[1][0] >= getBoundingBox()[1][0] && frog->getBoundingBox()[1][0] <= getBoundingBox()[0][0] &&
		frog->getBoundingBox()[1][2] <= getBoundingBox()[1][2] && frog->getBoundingBox()[1][2] >= getBoundingBox()[0][2]){
		frog->resetPosition();
	}
}