#include "Turtle.h"

Turtle::Turtle(bool side, float x, float y, float z){
	for (int i = 0; i < 7; i++){
		vsres[i] = new VSResSurfRevLib();
		vsres[i]->setMaterialBlockName("Materials");
	}

	vsml = VSMathLib::getInstance();
	setupObjects();

	actualPosition[0] = x;
	actualPosition[1] = y;
	actualPosition[2] = z;

	Turtle::side = side;
}

Turtle::~Turtle(){}

float* Turtle::getActualPostion(){
	return actualPosition;
}

void Turtle::setupObjects() {
	float body_amb[] = { 0.05f, 0.05f, 0.0f, 1.0f };
	float body_diff[] = { 0.1f, 0.55f, 0.1f, 1.0f };
	float body_spec[] = { 0.35f, 0.65f, 0.45f, 1.0f };
	float body_shininess[] = { 0.25f };

	float brown_amb[] = { 0.2125,0.1275,0.054 };
	float brown_diff[] = { 0.714,0.4284,0.18144 };
	float brown_spec[] = { 0.393548,0.271906,0.166721 };
	float brown_shininess[] = { 0.2f };


	vsres[0]->createSphere(1, 30);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, brown_diff);
	vsres[0]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[0]->setColor(VSResourceLib::SPECULAR, brown_spec);
	vsres[0]->setColor(VSResourceLib::SHININESS, brown_shininess);

	vsres[1]->createSphere(0.4f, 30);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[1]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[1]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[1]->setColor(VSResourceLib::SHININESS, brown_shininess);

	vsres[2]->createSphere(0.3f, 30);
	vsres[2]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[2]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[2]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[2]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[3]->createSphere(0.3f, 30);
	vsres[3]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[3]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[3]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[3]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[4]->createSphere(0.3f, 30);
	vsres[4]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[4]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[4]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[4]->setColor(VSResourceLib::SHININESS, body_shininess);

	vsres[5]->createCone(1,0.3f, 30);
	vsres[5]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[5]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[5]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[5]->setColor(VSResourceLib::SHININESS, body_shininess);
}

void Turtle::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->scale(1, 0.5, 1);
	vsml->translate(actualPosition[0] , actualPosition[1], actualPosition[2]);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1]-0.2, actualPosition[2]-1);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0]- 0.9, actualPosition[1]-0.3, actualPosition[2] - 0.7);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.9, actualPosition[1]-0.3, actualPosition[2] + 0.7);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] - 0.9, actualPosition[1]-0.3, actualPosition[2] + 0.7);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 0.9, actualPosition[1] - 0.3, actualPosition[2] - 0.7);
	vsres[4]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1] - 0.3, actualPosition[2] + 0.7);
	vsml->rotate(90, 1, 0, 0);
	vsres[5]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Turtle::move(){
	if (side){
		actualPosition[2] += 0.2f;
	}
	else
		actualPosition[2] -= 0.2f;
}