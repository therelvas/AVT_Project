#include "Frog.h"

Frog::Frog(float position[4], VSResourceLib* libClass){
	actualPosition[0] = position[0];
	actualPosition[1] = position[1];
	actualPosition[2] = position[2];
	actualPosition[3] = position[3];

	Frog::libClass = libClass;
}

Frog::~Frog(){}

float* Frog::getActualPostion(){
	return actualPosition;
}

float* Frog::getLastPosition(){
	return lastPosition;
}