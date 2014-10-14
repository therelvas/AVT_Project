#include "Frog.h"

Frog::Frog(){

	for (int i = 0; i < 6; i++){
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

void Frog::setupObjects() {
	
	float body_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float body_diff[] = { 0.1f, 0.35f, 0.1f, 1.0f };
	float body_spec[] = { 0.45f, 0.55f, 0.45f, 1.0f };
	float body_shininess[] = { 32.0f };

	float eyes_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//Head
	vsres[1]->createSphere(0.5f, 40);
	vsres[1]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[1]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[1]->setColor(VSResourceLib::SHININESS, body_shininess);

	//Eyes
	vsres[2]->createSphere(0.2f, 40);
	vsres[2]->setColor(VSResourceLib::AMBIENT, eyes_amb);

	vsres[3]->createSphere(0.2f, 40);
	vsres[3]->setColor(VSResourceLib::AMBIENT, eyes_amb);

	//Body
	vsres[0]->createCylinder(1.0f, 0.5f, 40);
	vsres[0]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[0]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[0]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[4]->createSphere(0.5f, 40);
	vsres[4]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[4]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[4]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[4]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[5]->createSphere(0.5f, 40);
	vsres[5]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[5]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[5]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[5]->setColor(VSResourceLib::SHININESS, body_shininess);
}

void Frog::render(VSShaderLib shader) {
	
	vsml->loadIdentity(VSMathLib::MODEL);
	
	//Head
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.5, actualPosition[1] + 0.5, actualPosition[2]);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Eyes
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.8, actualPosition[1] + 0.8, actualPosition[2] + 0.2);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.8, actualPosition[1] + 0.8, actualPosition[2] - 0.2);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Body
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0],actualPosition[1],actualPosition[2]);
	vsml->rotate(90, 1, 0, 0);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2]+0.5);
	vsres[4]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2]-0.5);
	vsres[5]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Frog::moveToFront(){
	actualPosition[0] += DISPLACEMENT;
}
void Frog::moveToBack(){
	actualPosition[0] -= DISPLACEMENT;
}
void Frog::moveToLeft(){
	actualPosition[2] -= DISPLACEMENT;
}
void Frog::moveToRight(){
	actualPosition[2] += DISPLACEMENT;
}