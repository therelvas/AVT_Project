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