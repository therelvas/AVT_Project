#include "Frog.h"

Frog::Frog(){
	for (int i = 0; i < 6; i++){
		vsres[i] = new VSResSurfRevLib();
		vsres[i]->setMaterialBlockName("Materials");
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
	
	float g[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float w[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	vsres[0]->createCylinder(1.0f, 0.5f, 30);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, g);
	vsres[0]->setColor(VSResourceLib::SPECULAR, g);

	vsres[1]->createSphere(0.5f, 30);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, g);
	vsres[1]->setColor(VSResourceLib::SPECULAR, g);

	vsres[2]->createSphere(0.2f, 30);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, w);
	vsres[2]->setColor(VSResourceLib::SPECULAR, w);

	vsres[3]->createSphere(0.2f, 30);
	vsres[3]->setColor(VSResourceLib::DIFFUSE, w);
	vsres[3]->setColor(VSResourceLib::SPECULAR, w);

	vsres[4]->createSphere(0.5f, 30);
	vsres[4]->setColor(VSResourceLib::DIFFUSE, g);
	vsres[4]->setColor(VSResourceLib::SPECULAR, g);

	vsres[5]->createSphere(0.5f, 30);
	vsres[5]->setColor(VSResourceLib::DIFFUSE, g);
	vsres[5]->setColor(VSResourceLib::SPECULAR, g);
}

void Frog::render() {
	
	//body
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0],actualPosition[1],actualPosition[2]);
	vsml->rotate(90, 1, 0, 0);
	vsres[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2]+0.5);
	vsres[4]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2]-0.5);
	vsres[5]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//head
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0]+0.5, actualPosition[1]+0.5, actualPosition[2]);
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
	vsml->translate(actualPosition[0] + 0.8, actualPosition[1] + 0.8, actualPosition[2]-0.2);
	vsres[3]->render();
	vsml->popMatrix(VSMathLib::MODEL);
}

void Frog::moveToFront(){
	actualPosition[0] += 0.2;
}
void Frog::moveToBack(){
	actualPosition[0] -= 0.2;
}
void Frog::moveToLeft(){
	actualPosition[2] -= 0.2;
}
void Frog::moveToRight(){
	actualPosition[2] += 0.2;
}