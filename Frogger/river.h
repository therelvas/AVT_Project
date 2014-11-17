#ifndef RIVER_H
#define RIVER_H

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "staticObject.h"
#include "cube.h"

class River : public StaticObject {

private:

	Cube *cube;

public:

	River(float x, float y, float z);
	~River();

	void setupObjects();
	void render(VSShaderLib shader);
};

#endif