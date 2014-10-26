#include "gameObject.h"

GameObject::GameObject(float x, float y, float z) {

	vsml = VSMathLib::getInstance();

	position[0] = x;
	position[1] = y;
	position[2] = z;

	initialPosition[0] = x;
	initialPosition[1] = y;
	initialPosition[2] = z;
}

GameObject::~GameObject(){}

float* GameObject::getPosition() {

	return position;
}


void GameObject::resetPosition() {

	position[0] = initialPosition[0];
	position[1] = initialPosition[1];
	position[2] = initialPosition[2];
}

bool GameObject::isInitialPos() {

	for (int i = 0; i < 3; i++) {
		if (position[i] != initialPosition[i])
			return false;
	}

	return true;
}

void GameObject::setupObjects(){}
void GameObject::render(VSShaderLib shader){}