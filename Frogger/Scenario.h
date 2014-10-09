#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"
#include "lib/vsResourceLib.h"

class Scenario{

private:

	float actualPosition[3];
	VSMathLib *vsml;
	VSResSurfRevLib *vsres[6];


public:
	Scenario();
	~Scenario();

	float* getActualPostion();

	void updatePosition(int x, int y, int z){
		actualPosition[0] = x;
		actualPosition[1] = y;
		actualPosition[2] = z;
	}

	void setupObjects();
	void render();
};
