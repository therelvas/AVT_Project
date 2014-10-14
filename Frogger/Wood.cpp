#include "Wood.h"

Wood::Wood(bool side, float x, float y, float z){
	for (int i = 0; i < 3; i++){
		vsres[i] = new VSResSurfRevLib();
		vsres[i]->setMaterialBlockName("Materials");
	}

	vsml = VSMathLib::getInstance();
	setupObjects();

	actualPosition[0] = x;
	actualPosition[1] = y;
	actualPosition[2] = z;

	Wood::side = side;
}

Wood::~Wood(){}

float* Wood::getActualPostion(){
	return actualPosition;
}

void Wood::setupObjects() {

	float brown_diff[4] = { 0.25f, 0.148f, 0.06475f, 1.0f };
	float body_amb[4] = { 0.4f, 0.2368f, 0.1036f, 1.0f };
	float brown_spec[4] = { 0.774597f, 0.458561f, 0.200621f, 1.0f };
	float body_shininess[] = { 76.8f };

	vsres[0]->createCylinder(5,0.5f, 30);
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
	vsml->translate(actualPosition[0] + 0.15, actualPosition[1], actualPosition[2]);
	vsml->rotate(90, 1, 0, 0);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15, actualPosition[1], actualPosition[2] + 2.5);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.15, actualPosition[1], actualPosition[2] - 2.5);
	vsres[2]->render(shader);
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