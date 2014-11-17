#ifndef FOG_H
#define FOG_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

#include "lib/vsShaderLib.h"
#include "lib/vsMathLib.h"

#include "constants.h"

class Fog {

private:

	int index;
	VSMathLib *vsml;

public:
	struct FogParameters {
		bool isEnabled;
		float vFogColorR; // Fog color
		float vFogColorG; // Fog color
		float vFogColorB; // Fog color
		float fStart; // This is only for linear fog
		float fEnd; // This is only for linear fog
		float fDensity; // For exp and exp2 equation

		int iEquation; // 0 = linear, 1 = exp, 2 = exp2
	} fogParams;

	Fog();
	~Fog();

	void draw(VSShaderLib shader);
};

#endif