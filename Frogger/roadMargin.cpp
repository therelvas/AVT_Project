#include "roadMargin.h"

RoadMargin::RoadMargin(float x, float y, float z) : StaticObject(x, y, z) {

	cube = new Cube();
	setupObjects();
}

void RoadMargin::setupObjects() {

	float road_margin_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float road_margin_diff[] = { 0.55f, 0.55f, 0.55f, 1.0f };
	float road_margin_spec[] = { 0.70f, 0.70f, 0.70f, 1.0f };
	float road_margin_shin[] = { 80.0f };

	//River
	cube->setColor(VSResourceLib::AMBIENT, road_margin_amb);
	cube->setColor(VSResourceLib::DIFFUSE, road_margin_diff);
	cube->setColor(VSResourceLib::SPECULAR, road_margin_spec);
	cube->setColor(VSResourceLib::SHININESS, road_margin_shin);
}

void RoadMargin::render(VSShaderLib shader) {

	vsml->loadIdentity(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(position[0], position[1], position[2]);
	vsml->scale(BORDER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}