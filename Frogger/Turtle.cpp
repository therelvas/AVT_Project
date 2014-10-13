#include "Turtle.h"

Turtle::Turtle(bool side){
	for (int i = 0; i < 7; i++){
		vsres[i] = new VSResSurfRevLib();
		vsres[i]->setMaterialBlockName("Materials");
	}

	vsml = VSMathLib::getInstance();
	setupObjects();

	actualPosition[0] = 15;
	actualPosition[1] = 0.5;
	actualPosition[2] = 0;

	Turtle::side = side;
}

Turtle::~Turtle(){}

float* Turtle::getActualPostion(){
	return actualPosition;
}

void Turtle::setupObjects() {

	float g[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float w[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float b[4] = { 0.5f, 0.3f, 0.0f, 1.0f };
	float r[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	vsres[0]->createSphere(1, 30);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[0]->setColor(VSResourceLib::AMBIENT, b);

	vsres[1]->createSphere(0.4f, 30);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[1]->setColor(VSResourceLib::AMBIENT, b);

	vsres[2]->createSphere(0.3f, 30);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[2]->setColor(VSResourceLib::AMBIENT, b);

	vsres[3]->createSphere(0.3f, 30);
	vsres[3]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[3]->setColor(VSResourceLib::AMBIENT, b);

	vsres[4]->createSphere(0.3f, 30);
	vsres[4]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[4]->setColor(VSResourceLib::AMBIENT, b);

	vsres[5]->createCone(1,0.3f, 30);
	vsres[5]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[5]->setColor(VSResourceLib::AMBIENT, b);
}

void Turtle::render() {

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->scale(1, 0.5, 1);
	vsml->translate(actualPosition[0] , actualPosition[1], actualPosition[2]);
	vsres[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1]-0.2, actualPosition[2]-1);
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0]- 0.9, actualPosition[1]-0.3, actualPosition[2] - 0.7);
	vsres[2]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.9, actualPosition[1]-0.3, actualPosition[2] + 0.7);
	vsres[2]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] - 0.9, actualPosition[1]-0.3, actualPosition[2] + 0.7);
	vsres[3]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.9, actualPosition[1] - 0.3, actualPosition[2] - 0.7);
	vsres[4]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->rotate(90, 1, 0, 0);
	vsres[5]->render();
	vsml->popMatrix(VSMathLib::MODEL);

/*	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15, actualPosition[1], actualPosition[2]);
	vsml->rotate(90, 1, 0, 0);
	vsres[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15, actualPosition[1], actualPosition[2] + 2.5);
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15, actualPosition[1], actualPosition[2] - 2.5);
	vsres[2]->render();
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

void Turtle::move(){
	if (side){
		actualPosition[2] += 0.2;
	}
	else
		actualPosition[2] -= 0.2;
}