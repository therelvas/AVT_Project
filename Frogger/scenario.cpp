#include "Scenario.h"

Scenario::Scenario(){
	
	for (int i = 0; i < 5; i++){
		cube[i] = new Cube();
	}
	
	defaultPosition[0] = 0;
	defaultPosition[1] = -1.5;
	defaultPosition[2] = 0;

	vsml = VSMathLib::getInstance();
	setupObjects();
}

Scenario::~Scenario(){}

void Scenario::setupObjects() {

	float water_amb[] = { 0.0f, 0.1f, 0.06f, 1.0f };
	float water_diff[] = { 0.0f, 0.50980392f, 0.50980392f, 1.0f };
	float water_spec[] = { 0.50196078f, 0.50196078f, 0.50196078f, 1.0f };
	float water_shin[] = { 32.0f };

	float river_margin_amb[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	float river_margin_diff[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
	float river_margin_spec[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
	float river_margin_shin[] = { 76.8f };

	float r_margin_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float r_margin_diff[] = { 0.55f, 0.55f, 0.55f, 1.0f };
	float r_margin_spec[] = { 0.70f, 0.70f, 0.70f, 1.0f };
	float r_margin_shin[] = { 32.0f };

	float road_amb[] = { 0.05375f, 0.05f, 0.06625f, 0.82f };
	float road_diff[] = { 0.18275f, 0.17f, 0.22525f, 0.82f };
	float road_spec[] = { 0.332741f, 0.328634f, 0.346435f, 0.82f };
	float road_shin[] = { 38.4f };

	//Road margin
	cube[0]->setColor(VSResourceLib::AMBIENT, r_margin_amb);
	cube[0]->setColor(VSResourceLib::DIFFUSE, r_margin_diff);
	cube[0]->setColor(VSResourceLib::SPECULAR, r_margin_spec);
	cube[0]->setColor(VSResourceLib::SHININESS, r_margin_shin);

	//Road
	cube[1]->setColor(VSResourceLib::AMBIENT, road_amb);
	cube[1]->setColor(VSResourceLib::DIFFUSE, road_diff);
	cube[1]->setColor(VSResourceLib::SPECULAR, road_spec);
	cube[1]->setColor(VSResourceLib::SHININESS, road_shin);

	//First river margin
	cube[2]->setColor(VSResourceLib::AMBIENT, river_margin_amb);
	cube[2]->setColor(VSResourceLib::DIFFUSE, river_margin_diff);
	cube[2]->setColor(VSResourceLib::SPECULAR, river_margin_spec);
	cube[2]->setColor(VSResourceLib::SHININESS, river_margin_shin);

	//River
	cube[3]->setColor(VSResourceLib::AMBIENT, water_amb);
	cube[3]->setColor(VSResourceLib::DIFFUSE, water_diff);
	cube[3]->setColor(VSResourceLib::SPECULAR, water_spec);
	cube[3]->setColor(VSResourceLib::SHININESS, water_shin);

	//Second river margin
	cube[4]->setColor(VSResourceLib::AMBIENT, river_margin_amb);
	cube[4]->setColor(VSResourceLib::DIFFUSE, river_margin_diff);
	cube[4]->setColor(VSResourceLib::SPECULAR, river_margin_spec);
	cube[4]->setColor(VSResourceLib::SHININESS, river_margin_shin);
}

void Scenario::render(VSShaderLib shader) {
	
	//Road margin
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(defaultPosition[0], defaultPosition[1], defaultPosition[2]);
	vsml->scale(BORDER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[0]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
	
	//Road
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(STREET_X, defaultPosition[1], defaultPosition[2]);
	vsml->scale(OTHER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[1]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
	
	//First river margin
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(BORDER2_X, defaultPosition[1], defaultPosition[2]);
	vsml->scale(BORDER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[2]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
	
	//River
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(WATER_X, defaultPosition[1], defaultPosition[2]);
	vsml->scale(OTHER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[3]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
	
	//Second river margin
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(BORDER3_X, defaultPosition[1], defaultPosition[2]);
	vsml->scale(BORDER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[4]->render(shader);
	vsml->popMatrix(VSMathLib::MODEL);
}