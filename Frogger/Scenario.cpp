#include "Scenario.h"

Scenario::Scenario(){
	for (int i = 0; i < 6; i++){
		vsres[i] = new VSResSurfRevLib();
	}

	vsml = VSMathLib::getInstance();
	setupObjects();
	actualPosition[0] = 0;
	actualPosition[1] = -2;
	actualPosition[2] = 0;
}

Scenario::~Scenario(){}

float* Scenario::getActualPostion(){
	return actualPosition;
}

void Scenario::setupObjects() {
	//vsres[1]->setColor(VSResourceLib::MaterialSemantics::AMBIENT, color);
	vsres[0]->createCylinder(1.0f, 0.5f, 30);
	vsres[1]->createCylinder(1.0f, 0.5f, 30);
	vsres[2]->createCylinder(1.0f, 0.5f, 30);
	vsres[3]->createCylinder(1.0f, 0.5f, 30);
	vsres[4]->createCylinder(1.0f, 0.5f, 30);
	vsres[5]->createCylinder(1.0f, 0.5f, 30);
}

void Scenario::render() {
	//border
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);
	vsres[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//road
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0]+3, actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//border
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 6, actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//water
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 9, actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);	vsres[1]->render();
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//border
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 12, actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);	vsres[1]->render();	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	//actualPosition[0] += 0.01;
	//actualPosition[1] += 0.01;
	//actualPosition[2] += 0;
}