#ifndef ROAD_H
#define ROAD_H

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "staticObject.h"
#include "cube.h"

class Road : public StaticObject {

private:

	Cube *cube;

public:

	Road(float x, float y, float z);
	~Road();

	void setupObjects();
	void render(VSShaderLib shader);
};

#endif