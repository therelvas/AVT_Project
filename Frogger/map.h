#ifndef MAP_H
#define MAP_H

#define SIZE_X 100
#define SIZE_Y 100

class Map {

private:

	float matrix[SIZE_X][SIZE_Y];

public : 

	Map();
	~Map();
	float getPositionValue(int x, int y);
	void updatePositionValue(int x, int y, float value);
};

#endif