#include "Scenario.h"

Scenario::Scenario(){
	for (int i = 0; i < 5; i++){
		cube[i] = new Cube();
	}
	defaultPosition[0] = 0;
	defaultPosition[1] = -1.5;
	defaultPosition[2] = -50;

	vsml = VSMathLib::getInstance();
}

Scenario::~Scenario(){}

void Scenario::render() {
	//border
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(defaultPosition[0], defaultPosition[1], defaultPosition[2]);
	vsml->scale(BORDER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//street
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(STREET_X, defaultPosition[1], defaultPosition[2]);
	vsml->scale(OTHER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//border
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(BORDER2_X, defaultPosition[1], defaultPosition[2]);
	vsml->scale(BORDER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[2]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//water
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(WATER_X, defaultPosition[1], defaultPosition[2]);
	vsml->scale(OTHER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[3]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//border
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(BORDER3_X, defaultPosition[1], defaultPosition[2]);
	vsml->scale(BORDER_SCALE_FACTOR_X, 1, SCALE_FACTOR_Z);
	cube[4]->render();
	vsml->popMatrix(VSMathLib::MODEL);
}