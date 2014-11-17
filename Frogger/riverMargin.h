#ifndef RIVERMARGIN_H
#define RIVERMARGIN_H

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "staticObject.h"
#include "cube.h"

class RiverMargin : public StaticObject {

private:

	Cube *cube;

public:

	RiverMargin(float x, float y, float z);
	~RiverMargin();

	void setupObjects();
	void render(VSShaderLib shader);
};

#endif