#include "Frog.h"

Frog::Frog(float x, float y, float z){

	for (int i = 0; i < 6; i++){
		vsres[i] = new VSResSurfRevLib();
	}

	vsml = VSMathLib::getInstance();
	setupObjects();
	actualPosition[0] = x;
	actualPosition[1] = y;
	actualPosition[2] = z; 
}

Frog::~Frog(){}

float* Frog::getActualPostion(){
	return actualPosition;
}

void Frog::setupObjects() {
	
	float body_amb[] = { 0.05f, 0.05f, 0.0f, 1.0f };
	float body_diff[] = { 0.1f, 0.55f, 0.1f, 1.0f };
	float body_spec[] = { 0.35f, 0.65f, 0.45f, 1.0f };
	float body_shininess[] = { 0.25f };

	float eyes_diff[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//Head
	vsres[1]->createSphere(0.5f, 40);
	vsres[1]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[1]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[1]->setColor(VSResourceLib::SHININESS, body_shininess);

	//Eyes
	vsres[2]->createSphere(0.2f, 40);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, eyes_diff);
	vsres[2]->setColor(VSResourceLib::SPECULAR, eyes_diff);

	vsres[3]->createSphere(0.2f, 40);
	vsres[3]->setColor(VSResourceLib::DIFFUSE, eyes_diff);
	vsres[3]->setColor(VSResourceLib::SPECULAR, eyes_diff);

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
	
	//Head
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.5f, actualPosition[1] + 0.5f, actualPosition[2]);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Eyes
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.8f, actualPosition[1] + 0.8f, actualPosition[2] + 0.2f);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.8f, actualPosition[1] + 0.8f, actualPosition[2] - 0.2f);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Body
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0],actualPosition[1],actualPosition[2]);
	vsml->rotate(90.0f, 1.0f, 0.0f, 0.0f);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2] + 0.5f);
	vsres[4]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2] - 0.5f);
	vsres[5]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Frog::moveToFront(){
	actualPosition[0] += 0.2f;
}
void Frog::moveToBack(){
	actualPosition[0] -= 0.2f;
}
void Frog::moveToLeft(){
	actualPosition[2] -= 0.2f;
}
void Frog::moveToRight(){
	actualPosition[2] += 0.2f;
}