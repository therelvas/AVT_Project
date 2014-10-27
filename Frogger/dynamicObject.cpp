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
	if (!(position[0] + x*speed <= 32 && position[0] + x*speed >= 0))
		return;
	if (!(position[2] + z*speed <= 100 && position[2] + z*speed >= 0))
		return;

	position[0] += x * speed;
	position[1] += y * speed;
	position[2] += z * speed;
}

void DynamicObject::collide(DynamicObject* frog){
	return;
}

float** DynamicObject::getBoundingBox(){
	return NULL;
}
