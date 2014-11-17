#ifndef ROADMARGIN_H
#define ROADMARGIN_H

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "staticObject.h"
#include "cube.h"

class RoadMargin : public StaticObject {

private:

	Cube *cube;

public:

	RoadMargin(float x, float y, float z);
	~RoadMargin();

	void setupObjects();
	void render(VSShaderLib shader);
};

#endif