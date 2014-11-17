#include "road.h"

Road::Road(float x, float y, float z) : StaticObject(x, y, z) {

	cube = new Cube();
	setupObjects();
}

void Road::setupObjects() {

	float road_amb[] = { 0.05375f, 0.05f, 0.06625f, 1.0f };
	float road_diff[] = { 0.18275f, 0.17f, 0.22525f, 1.0f };
	float road_spec[] = { 0.332741f, 0.328634f, 0.346435f, 1.0f };
	float road_shin[] = { 80.0f };

	cube->addTexture(0, "assets/road3.jpg");
	cube->setColor(VSResourceLib::AMBIENT, road_amb);
	cube->setColor(VSResourceLib::DIFFUSE, road_diff);
	cube->setColor(VSResourceLib::SPECULAR, road_spec);
	cube->setColor(VSResourceLib::SHININESS, road_shin);
}


void Road::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2]);
	vsml->scale(SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}