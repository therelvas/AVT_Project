#include "Wood.h"

Wood::Wood(bool side){
	for (int i = 0; i < 3; i++){
		vsres[i] = new VSResSurfRevLib();
		vsres[i]->setMaterialBlockName("Materials");
	}

	vsml = VSMathLib::getInstance();
	setupObjects();

	actualPosition[0] = 10;
	actualPosition[1] = 0.5;
	actualPosition[2] = 0;

	Wood::side = side;
}

Wood::~Wood(){}

float* Wood::getActualPostion(){
	return actualPosition;
}

void Wood::setupObjects() {

	float g[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float w[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float b[4] = { 0.5f, 0.3f, 0.0f, 1.0f };
	float r[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	vsres[0]->createCylinder(5,0.5f, 30);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[0]->setColor(VSResourceLib::AMBIENT, b);

	vsres[1]->createSphere(0.5f, 30);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[1]->setColor(VSResourceLib::AMBIENT, b);

	vsres[2]->createSphere(0.5f, 30);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, b);
	vsres[2]->setColor(VSResourceLib::AMBIENT, b);
}

void Wood::render() {

	vsml->loadIdentity(VSMathLib::MODEL);
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

void Wood::move(){
	if (side){
		actualPosition[2] += 0.2;
	}
	else
		actualPosition[2] -= 0.2;
}