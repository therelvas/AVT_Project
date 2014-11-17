#include "riverMargin.h"

RiverMargin::RiverMargin(float x, float y, float z) : StaticObject(x, y, z) {

	cube = new Cube();
	setupObjects();
}

void RiverMargin::setupObjects() {

	float river_margin_amb[] = { 0.0215f, 0.1745f, 0.0215f, 1.0f };
	float river_margin_diff[] = { 0.07568f, 0.61424f, 0.07568f, 1.0f };
	float river_margin_spec[] = { 0.633f, 0.727811f, 0.633f, 1.0f };
	float river_margin_shin[] = { 80.0f };

	//River
	cube->setColor(VSResourceLib::AMBIENT, river_margin_amb);
	cube->setColor(VSResourceLib::DIFFUSE, river_margin_diff);
	cube->setColor(VSResourceLib::SPECULAR, river_margin_spec);
	cube->setColor(VSResourceLib::SHININESS, river_margin_shin);
}

void RiverMargin::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2]);
	vsml->scale(BORDER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}