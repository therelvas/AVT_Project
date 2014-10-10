#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

#include "Cube.h"

class Scenario{

private:

	VSMathLib *vsml;
	VSResSurfRevLib *vsres[6];
	Cube* cube[6];


public:
	Scenario();
	~Scenario();

	void setupObjects();
	void render();
};
