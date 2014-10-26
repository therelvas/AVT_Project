#ifndef SCENARIO_H
#define SCENARIO_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "cube.h"
#include "staticObject.h"
#include "constants.h"

class Scenario : public StaticObject {

private:

	Cube *cube[5];

public:

	Scenario(float x, float y, float z);
	~Scenario();

	void setupObjects();
	void render(VSShaderLib shader);
};

#endif