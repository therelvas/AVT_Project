#include "Map.h"

Map::Map(){
}

Map::~Map(){
}

float Map::getPositionValue(int x, int y){
	return matrix[x][y];
}

void Map::updatePositionValue(int x, int y, float value){
	matrix[x][y] = value;
}