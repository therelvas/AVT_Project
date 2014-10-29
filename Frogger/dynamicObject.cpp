#include "dynamicObject.h"

DynamicObject::DynamicObject(float x, float y, float z) : GameObject(x, y, z) {}

DynamicObject::~DynamicObject(){}

void DynamicObject::setupObjects() {}
void DynamicObject::render(VSShaderLib shader) {}

void DynamicObject::move(float x, float y, float z, float speed) {

	position[0] += x * speed;
	position[1] += y * speed;
	position[2] += z * speed;
}

void DynamicObject::moveFrog(float x, float y, float z, float speed) {
	//this is need so that the frog knows the limits of the game
	if (!(position[0] + x*speed <= 32 && position[0] + x*speed >= 0))
		return;
	if (!(position[2] + z*speed <= 100 && position[2] + z*speed >= 0))
		return;

	position[0] += x * speed;
	position[1] += y * speed;
	position[2] += z * speed;
}

void DynamicObject::collide(DynamicObject* frog){}

//does not need to be implemented
float** DynamicObject::getBoundingBox(){
	return NULL;
}

void DynamicObject::loseLife(){}

int DynamicObject::getLifes(){
	return 0;
}
void DynamicObject::resetLifes(){}
