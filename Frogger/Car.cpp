#include "Car.h"

Car::Car(bool side, float x, float y, float z){

	for (int i = 0; i < 6; i++){
		vsres[i] = new VSResSurfRevLib();

	}

	vsml = VSMathLib::getInstance();
	setupObjects();

	actualPosition[0] = x;
	actualPosition[1] = y;
	actualPosition[2] = z;

	Car::side = side;
}

Car::~Car(){}

float* Car::getActualPostion(){
	return actualPosition;
}

void Car::setupObjects() {


	cube[0] = new Cube();
	cube[1] = new Cube();

	float body_amb[] = { 0.0,0.0,0.0 };
	float body_diff[] = { 0.5,0.0,0.0 };
	float body_spec[] = { 0.7,0.6,0.6 };
	float body_shininess[] = { 0.25 };

	float tires_diff[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	cube[0]->setColor(VSResourceLib::AMBIENT, body_amb);
	cube[0]->setColor(VSResourceLib::DIFFUSE, body_diff);
	cube[0]->setColor(VSResourceLib::SPECULAR, body_spec);
	cube[0]->setColor(VSResourceLib::SHININESS, body_shininess);
	//Road
	cube[1]->setColor(VSResourceLib::AMBIENT, body_amb);
	cube[1]->setColor(VSResourceLib::DIFFUSE, body_diff);
	cube[1]->setColor(VSResourceLib::SPECULAR, body_spec);
	cube[1]->setColor(VSResourceLib::SHININESS, body_shininess);

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
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2]);
	vsml->scale(2, 1, 5);
	cube[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1]+1, actualPosition[2]+1);
	vsml->scale(2,1,3);
	cube[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//wheels
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0]+0.15, actualPosition[1], actualPosition[2]+1);
	vsml->scale(0.5, 1, 1);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15, actualPosition[1], actualPosition[2] + 4);
	vsml->scale(0.5, 1, 1);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 1.85, actualPosition[1], actualPosition[2] + 4);
	vsml->scale(0.5, 1, 1);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 1.85, actualPosition[1], actualPosition[2] + 1);
	vsml->scale(0.5, 1, 1);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Car::move(){
	if (side){
		actualPosition[2] += 0.2f;
	}
	else
		actualPosition[2] -= 0.2f;
}