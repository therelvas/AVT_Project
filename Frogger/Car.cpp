#include "Car.h"

Car::Car(bool side){
	for (int i = 0; i < 6; i++){
		vsres[i] = new VSResSurfRevLib();

	}

	vsml = VSMathLib::getInstance();
	setupObjects();

	actualPosition[0] = 3;
	actualPosition[1] = 0.5;
	actualPosition[2] = 0;

	Car::side = side;
}

Car::~Car(){}

float* Car::getActualPostion(){
	return actualPosition;
}

void Car::setupObjects() {


	cube[0] = new Cube();
	cube[1] = new Cube();

	float g[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float w[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float b[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float r[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	vsres[0]->createSphere(0.5f, 30);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[0]->setColor(VSResourceLib::SPECULAR, b);

	vsres[1]->createSphere(0.5f, 30);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[1]->setColor(VSResourceLib::SPECULAR, b);

	vsres[2]->createSphere(0.5f, 30);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[2]->setColor(VSResourceLib::SPECULAR, b);

	vsres[3]->createSphere(0.5f, 30);
	vsres[3]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[3]->setColor(VSResourceLib::SPECULAR, b);

	vsres[4]->createSphere(0.5f, 30);
	vsres[4]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[4]->setColor(VSResourceLib::SPECULAR, b);
}

void Car::render() {

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2]);
	vsml->scale(2, 1, 5);
	cube[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1]+1, actualPosition[2]+1);
	vsml->scale(2,1,3);
	cube[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	//wheels
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0]+0.15, actualPosition[1], actualPosition[2]+1);
	vsml->scale(0.5, 1, 1);
	vsres[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15, actualPosition[1], actualPosition[2] + 4);
	vsml->scale(0.5, 1, 1);
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 1.85, actualPosition[1], actualPosition[2] + 4);
	vsml->scale(0.5, 1, 1);
	vsres[2]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 1.85, actualPosition[1], actualPosition[2] + 1);
	vsml->scale(0.5, 1, 1);
	vsres[3]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	/*vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2] - 0.5);
	vsres[5]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//head
	/*vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.5, actualPosition[1] + 0.5, actualPosition[2]);
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//eyes
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.8, actualPosition[1] + 0.8, actualPosition[2] + 0.2);
	vsres[2]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.8, actualPosition[1] + 0.8, actualPosition[2] - 0.2);
	vsres[3]->render();
	vsml->popMatrix(VSMathLib::MODEL);*/
}

void Car::move(){
	if (side){
		actualPosition[2] += 0.2;
	}
	else
		actualPosition[2] -= 0.2;
}