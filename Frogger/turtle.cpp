#include "Turtle.h"

Turtle::Turtle(float x, float y, float z) : DynamicObject(x, y, z) {
	
	for (int i = 0; i < 7; i++){
		vsres[i] = new VSResSurfRevLib();
	}

	setupObjects();
}

Turtle::~Turtle(){}

void Turtle::setupObjects() {

	float body_amb[] = { 0.05f, 0.05f, 0.0f, 1.0f };
	float body_diff[] = { 0.1f, 0.55f, 0.1f, 1.0f };
	float body_spec[] = { 0.35f, 0.65f, 0.45f, 1.0f };
	float body_shininess[] = { 0.25f };

	float brown_amb[] = { 0.2125f, 0.1275f, 0.054f };
	float brown_diff[] = { 0.714f, 0.4284f, 0.18144f };
	float brown_spec[] = { 0.393548f, 0.271906f, 0.166721f };
	float brown_shininess[] = { 0.2f };

	//Shell
	vsres[0]->createSphere(1.0f, 30);
	vsres[0]->setColor(VSResourceLib::DIFFUSE, brown_diff);
	vsres[0]->setColor(VSResourceLib::AMBIENT, brown_amb);
	vsres[0]->setColor(VSResourceLib::SPECULAR, brown_spec);
	vsres[0]->setColor(VSResourceLib::SHININESS, brown_shininess);

	//Head
	vsres[1]->createSphere(0.4f, 30);
	vsres[1]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[1]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[1]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[1]->setColor(VSResourceLib::SHININESS, brown_shininess);

	//Paws
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

	vsres[5]->createSphere(0.3f, 30);
	vsres[5]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[5]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[5]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[5]->setColor(VSResourceLib::SHININESS, body_shininess);

	//Tail
	vsres[6]->createCone(1.0f, 0.3f, 30);
	vsres[6]->setColor(VSResourceLib::DIFFUSE, body_diff);
	vsres[6]->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres[6]->setColor(VSResourceLib::SPECULAR, body_spec);
	vsres[6]->setColor(VSResourceLib::SHININESS, body_shininess);
}

void Turtle::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);
	
	//Shell
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->scale(1.0f, 0.4f, 1.0f);
	vsml->translate(position[0], position[1], position[2]);
	vsres[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Head
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1] - 0.2f, position[2] - 1.0f);
	vsres[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Paws
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] - 0.9f, position[1] - 0.3f, position[2] - 0.7f);
	vsres[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.9f, position[1] - 0.3f, position[2] + 0.7f);
	vsres[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] - 0.9f, position[1] - 0.3f, position[2] + 0.7f);
	vsres[4]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.9f, position[1] - 0.3f, position[2] - 0.7f);
	vsres[5]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);

	//Tail
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1] - 0.3f, position[2] + 0.7f);
	vsml->rotate(90.0f, 1.0f, 0.0f, 0.0f);
	vsres[6]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Turtle::move(float x, float y, float z, float speed) {

	position[0] += 0.0f * speed;
	position[1] += 0.0f * speed;
	position[2] -= 0.1f * speed;
}

float** Turtle::getBoundingBox(){

	float** boundingBox = 0;

	boundingBox = new float*[2];
	boundingBox[0] = new float[3];
	boundingBox[1] = new float[3];

	boundingBox[0][0] = position[0] + 1.5f;
	boundingBox[0][1] = 0;
	boundingBox[0][2] = position[2] - 2.4f;

	boundingBox[1][0] = position[0] - 1.5f;
	boundingBox[1][1] = 0;
	boundingBox[1][2] = position[2] + 2.4f;

	return boundingBox;
}

void Turtle::collide(DynamicObject* dynamicObject){


	if (dynamicObject->getBoundingBox()[0][0] >= getBoundingBox()[1][0] && dynamicObject->getBoundingBox()[0][0] <= getBoundingBox()[0][0]
		&&
		dynamicObject->getBoundingBox()[0][2] <= getBoundingBox()[1][2] && dynamicObject->getBoundingBox()[0][2] >= getBoundingBox()[0][2]){
		dynamicObject->collided = true;
		return;
	}
	if (dynamicObject->getBoundingBox()[1][0] >= getBoundingBox()[1][0] && dynamicObject->getBoundingBox()[1][0] <= getBoundingBox()[0][0] &&
		dynamicObject->getBoundingBox()[1][2] <= getBoundingBox()[1][2] && dynamicObject->getBoundingBox()[1][2] >= getBoundingBox()[0][2]){
		dynamicObject->collided = true;
		return;
	}
}