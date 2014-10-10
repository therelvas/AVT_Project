#include "Scenario.h"

Scenario::Scenario(){
	for (int i = 0; i < 6; i++){
		cube[i] = new Cube();
	}

	vsml = VSMathLib::getInstance();
}

Scenario::~Scenario(){}

void Scenario::render() {
	//border
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(0, -1.5, -50);
	vsml->scale(4, 1, 100);
	cube[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(4, -1.5, -50);
	vsml->scale(10, 1, 100);
	cube[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);

	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(14, -1.5, -50);
	vsml->scale(4, 1, 100);
	cube[2]->render();
	vsml->popMatrix(VSMathLib::MODEL);



	/*vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0], actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);
	vsres[0]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//road
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0]+3, actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//border
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 6, actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//water
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 9, actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);	vsres[1]->render();
	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);
	//border
	vsml->loadIdentity(VSMathLib::MODEL);
	vsml->pushMatrix(VSMathLib::MODEL);
	vsml->translate(actualPosition[0] + 12, actualPosition[1], actualPosition[2]);
	vsml->scale(3, 1, 100);	vsres[1]->render();	vsres[1]->render();
	vsml->popMatrix(VSMathLib::MODEL);*/

	//actualPosition[0] += 0.01;
	//actualPosition[1] += 0.01;
	//actualPosition[2] += 0;
}