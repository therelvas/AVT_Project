#include "Frog.h"

Frog::Frog(){
	
	vsres[0] = new VSResSurfRevLib();
	vsres[1] = new VSResSurfRevLib();

	vsml = VSMathLib::getInstance();
	setupObjects();
	/*
	actualPosition[0] = position[0];
	actualPosition[1] = position[1];
	actualPosition[2] = position[2];
	actualPosition[3] = position[3]; */
}

Frog::~Frog(){}

float* Frog::getActualPostion(){
	return actualPosition;
}

float* Frog::getLastPosition(){
	return lastPosition;
}

void Frog::setupObjects() {

	vsres[0]->createCylinder(2.0f, 0.5f, 30);
	vsres[1]->createSphere(1.0f, 30);
}

void Frog::render() {
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	translate();
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
}

void Frog::translate(){
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(2, 0, 0);
	vsres[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);
}