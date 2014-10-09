#include "Frog.h"

Frog::Frog(){
	for (int i = 0; i < 2; i++){
		vsres[i] = new VSResSurfRevLib();
	}

	vsml = VSMathLib::getInstance();
	setupObjects();
	actualPosition[0] = 0;
	actualPosition[1] = 0;
	actualPosition[2] = 0; 
}

Frog::~Frog(){}

float* Frog::getActualPostion(){
	return actualPosition;
}

float* Frog::getLastPosition(){
	return lastPosition;
}

void Frog::setupObjects() {
	//vsres[1]->setColor(VSResourceLib::MaterialSemantics::AMBIENT, color);
	vsres[0]->createCylinder(1.0f, 0.5f, 30);
	vsres[1]->createSphere(0.5f, 30);
}

void Frog::render() {

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0],actualPosition[1],actualPosition[2]);
	vsres[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(-actualPosition[0]+0.5, actualPosition[1]+0.5, actualPosition[2]);
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	//actualPosition[0] += 0.01;
	//actualPosition[1] += 0.01;
	//actualPosition[2] += 0;
}