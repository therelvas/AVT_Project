#include "river.h"

River::River(float x, float y, float z) : StaticObject(x, y, z) {

	cube = new Cube();
	setupObjects();
}

void River::setupObjects() {

	float water_amb[] = { 0.0f, 0.1f, 0.06f, 0.5f };
	float water_diff[] = { 0.0f, 0.50980392f, 0.50980392f, 0.5f };
	float water_spec[] = { 0.50196078f, 0.50196078f, 0.50196078f, 0.5f };
	float water_shin[] = { 80.0f };

	//River
	cube->addTexture(0, "assets/river2.png");
	cube->setColor(VSResourceLib::AMBIENT, water_amb);
	cube->setColor(VSResourceLib::DIFFUSE, water_diff);
	cube->setColor(VSResourceLib::SPECULAR, water_spec);
	cube->setColor(VSResourceLib::SHININESS, water_shin);
}

void River::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2]);
	vsml->scale(SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}