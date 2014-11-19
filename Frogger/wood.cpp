#include "wood.h"

Wood::Wood(float x, float y, float z) : DynamicObject(x, y, z) {
	
	vsres = new VSResSurfRevLib();

	setupObjects();
}

Wood::~Wood(){}

void Wood::setupObjects() {

	float brown_diff[4] = { 0.25f, 0.148f, 0.06475f, 1.0f };
	float body_amb[4] = { 0.4f, 0.2368f, 0.1036f, 1.0f };
	float brown_spec[4] = { 0.774597f, 0.458561f, 0.200621f, 1.0f };
	float body_shininess[] = { 76.8f };

	vsres->createCylinder(10.0f, 1.0f, 30);
	vsres->addTexture(0, "assets/wood.jpg");
	vsres->setColor(VSResourceLib::DIFFUSE, brown_diff);
	vsres->setColor(VSResourceLib::AMBIENT, body_amb);
	vsres->setColor(VSResourceLib::SPECULAR, brown_spec);
	vsres->setColor(VSResourceLib::SHININESS, body_shininess);
}

void Wood::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);
	
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0] + 0.15f, position[1], position[2]);
	vsml->rotate(90.0f, 1.0f, 0.0f, 0.0f);
	vsres->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}

void Wood::move(float x, float y, float z, float speed) {

	position[0] += 0.0f * speed;
	position[1] += 0.0f * speed;
	position[2] += 0.2f * speed;
}

float** Wood::getBoundingBox() {

	float** boundingBox = 0;

	boundingBox = new float*[2];
	boundingBox[0] = new float[3];
	boundingBox[1] = new float[3];

	boundingBox[0][0] = position[0] + 1.0f;
	boundingBox[0][1] = 0;
	boundingBox[0][2] = position[2] - 5.0f;

	boundingBox[1][0] = position[0] - 1.0f;
	boundingBox[1][1] = 0;
	boundingBox[1][2] = position[2] + 5.0f;

	return boundingBox;
}

void Wood::collide(DynamicObject* dynamicObject){


	if (dynamicObject->getBoundingBox()[0][0] >= getBoundingBox()[1][0] && dynamicObject->getBoundingBox()[0][0] <= getBoundingBox()[0][0]
		&&
		dynamicObject->getBoundingBox()[0][2] <= getBoundingBox()[1][2] && dynamicObject->getBoundingBox()[0][2] >= getBoundingBox()[0][2]){
		dynamicObject->loseLife();
		dynamicObject->resetPosition();
	}
	else if (dynamicObject->getBoundingBox()[1][0] >= getBoundingBox()[1][0] && dynamicObject->getBoundingBox()[1][0] <= getBoundingBox()[0][0] &&
		dynamicObject->getBoundingBox()[1][2] <= getBoundingBox()[1][2] && dynamicObject->getBoundingBox()[1][2] >= getBoundingBox()[0][2]){
		dynamicObject->loseLife();
		dynamicObject->resetPosition();
	}
}