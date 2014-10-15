#include "Wood.h"

Wood::Wood(bool side, float x, float y, float z){
	
	for (int i = 0; i < 3; i++){
		vsres[i] = new VSResSurfRevLib();
	}

	vsml = VSMathLib::getInstance();
	setupObjects();

	actualPosition[0] = x;
	actualPosition[1] = y;
	actualPosition[2] = z;

	Wood::side = side;
}

Wood::~Wood(){}

float* Wood::getActualPosition(){
	return actualPosition;
}

void Wood::setupObjects() {

	float brown_diff[4] = { 0.25f, 0.148f, 0.06475f, 1.0f };
	float body_amb[4] = { 0.4f, 0.2368f, 0.1036f, 1.0f };
	float brown_spec[4] = { 0.774597f, 0.458561f, 0.200621f, 1.0f };
	float body_shininess[] = { 76.8f };

	vsres[0]->createCylinder(5.0f, 0.5f, 30);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, brown_diff);
	vsres[0]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[0]->setColor(VSResourceLib::SPECULAR, brown_spec);
	vsres[0]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[1]->createSphere(0.5f, 30);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, brown_diff);
	vsres[1]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[1]->setColor(VSResourceLib::SPECULAR, brown_spec);
	vsres[1]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[2]->createSphere(0.5f, 30);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, brown_diff);
	vsres[2]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[2]->setColor(VSResourceLib::SPECULAR, brown_spec);
	vsres[2]->setColor(VSResourceLib::SHININESS, body_shininess);
}

void Wood::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15f, actualPosition[1], actualPosition[2]);
	vsml->rotate(90.0f, 1.0f, 0.0f, 0.0f);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15f, actualPosition[1], actualPosition[2] + 2.5f);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15f, actualPosition[1], actualPosition[2] - 2.5f);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Wood::move(float lvl){

	if (side){
		actualPosition[2] += 0.2f*lvl;
	}
	else
		actualPosition[2] -= 0.2f*lvl;
}