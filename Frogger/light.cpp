#include "light.h"

Light::Light() {

	index = 0;
	vsml = VSMathLib::getInstance();

	for (int i = 0; i < MAX_LIGHTS; i++) {
		myLightSources[i].isEnabled = false;
	}
}

Light::~Light() {}

void Light::addLight(LightTypes lightTypes, float *pos, float *spotDir, float spotCutOff, int index) {

	if (index < MAX_LIGHTS) {

		switch (lightTypes)
		{
		case DIRECTIONAL:
			myLightSources[index].isEnabled = true;
			myLightSources[index].isLocal = false;
			myLightSources[index].isSpot = false;
			memcpy(myLightSources[index].l_pos, pos, sizeof(float)* 4);
			break;

		case POINT:
			myLightSources[index].isEnabled = false;
			myLightSources[index].isLocal = true;
			myLightSources[index].isSpot = false;
			memcpy(myLightSources[index].l_pos, pos, sizeof(float)* 4);
			break;

		case SPOT:
			myLightSources[index].isEnabled = false;
			myLightSources[index].isLocal = true;
			myLightSources[index].isSpot = true;
			memcpy(myLightSources[index].l_pos, pos, sizeof(float)* 4);
			memcpy(myLightSources[index].l_spotDir, spotDir, sizeof(float)* 4);
			myLightSources[index].l_spotCutOff = spotCutOff;
			break;
		}
	}
}

void Light::draw(VSShaderLib shader) {

	GLint loc;
	float res[4];
	char s[25];

	for (int i = 0; i < MAX_LIGHTS; i++) {

		//Enabled bool
		sprintf(s, "lights[%d].isEnabled", i);
		loc = glGetUniformLocation(shader.getProgramIndex(), s);
		glUniform1i(loc, myLightSources[i].isEnabled);

		//Local bool
		sprintf(s, "lights[%d].isLocal", i);
		loc = glGetUniformLocation(shader.getProgramIndex(), s);
		glUniform1i(loc, myLightSources[i].isLocal);

		//Spot bool
		sprintf(s, "lights[%d].isSpot", i);
		loc = glGetUniformLocation(shader.getProgramIndex(), s);
		glUniform1i(loc, myLightSources[i].isSpot);

		if (myLightSources[i].isLocal) {

			//Light position
			sprintf(s, "lights[%d].l_pos", i);
			vsml->multMatrixPoint(VSMathLib::VIEW, myLightSources[i].l_pos, res);
			loc = glGetUniformLocation(shader.getProgramIndex(), s);
			glUniform4fv(loc, 1, res);

			if (myLightSources[i].isSpot) {

				//Spotlight direction
				sprintf(s, "lights[%d].l_spotDir", i);
				vsml->multMatrixPoint(VSMathLib::VIEW, myLightSources[i].l_spotDir, res);
				loc = glGetUniformLocation(shader.getProgramIndex(), s);
				glUniform4fv(loc, 1, res);

				//Spotlight cutoff
				sprintf(s, "lights[%d].l_spotCutOff", i);
				loc = glGetUniformLocation(shader.getProgramIndex(), s);
				glUniform1f(loc, myLightSources[i].l_spotCutOff);
			}
		}
		else {

			//Light position
			sprintf(s, "lights[%d].l_pos", i);
			vsml->multMatrixPoint(VSMathLib::VIEW, myLightSources[i].l_pos, res);
			loc = glGetUniformLocation(shader.getProgramIndex(), s);
			glUniform4fv(loc, 1, res);
		}
	}
}

void Light::switchLight(int index) {

	if (myLightSources[index].isEnabled) {
		myLightSources[index].isEnabled = false;
	}
	else {
		myLightSources[index].isEnabled = true;
	}
}

void Light::updateSpotPosDir(int index, float *pos, float *spotDir) {

	memcpy(myLightSources[index].l_pos, pos, sizeof(float)* 4);
	memcpy(myLightSources[index].l_spotDir, spotDir, sizeof(float)* 4);
}