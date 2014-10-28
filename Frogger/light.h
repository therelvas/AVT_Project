#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

#include "lib/vsShaderLib.h"
#include "lib/vsMathLib.h"

#include "constants.h"

class Light {

private:

	int index;
	VSMathLib *vsml;

	struct LightSource {

		bool isEnabled;
		bool isLocal;
		bool isSpot;
		float l_pos[4];
		float l_spotDir[4];
		float l_spotCutOff;
	};

	LightSource myLightSources[MAX_LIGHTS];
	
public:

	Light();
	~Light();

	enum LightTypes {

		DIRECTIONAL,
		POINT,
		SPOT,
	};

	void addLight(LightTypes lightType, float *pos, float *spotDir, float spotCutOff, int index);
	void switchLight(LightTypes lightType);
	void draw(VSShaderLib shader);

	void updateSpotPosDir(int index, float *pos, float *spotDir);
};

#endif