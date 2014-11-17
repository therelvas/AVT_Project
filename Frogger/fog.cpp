#include "fog.h"

Fog::Fog() {

	index = 0;
	vsml = VSMathLib::getInstance();

	fogParams.isEnabled = false;
	fogParams.fDensity = 0.04f;
	fogParams.vFogColorR = 0.7f;
	fogParams.vFogColorG = 0.7f;
	fogParams.vFogColorB = 0.7f;
	fogParams.fStart = 10.0f;
	fogParams.fEnd = 75.0f;
	fogParams.iEquation = FOG_EQUATION_EXP; // 0 = linear, 1 = exp, 2 = exp2
}

Fog::~Fog() {}

void Fog::draw(VSShaderLib shader) {

	GLint loc;

	loc = glGetUniformLocation(shader.getProgramIndex(), "fogParams.isEnabled");
	glUniform1i(loc, fogParams.isEnabled);

	loc = glGetUniformLocation(shader.getProgramIndex(), "fogParams.vFogColorR");
	glUniform1f(loc, fogParams.vFogColorR);

	loc = glGetUniformLocation(shader.getProgramIndex(), "fogParams.vFogColorG");
	glUniform1f(loc, fogParams.vFogColorG);

	loc = glGetUniformLocation(shader.getProgramIndex(), "fogParams.vFogColorB");
	glUniform1f(loc, fogParams.vFogColorB);

	loc = glGetUniformLocation(shader.getProgramIndex(), "fogParams.fStart");
	glUniform1f(loc, fogParams.fStart);

	loc = glGetUniformLocation(shader.getProgramIndex(), "fogParams.fEnd");
	glUniform1f(loc, fogParams.fEnd);

	loc = glGetUniformLocation(shader.getProgramIndex(), "fogParams.fDensity");
	glUniform1f(loc, fogParams.fDensity);

	loc = glGetUniformLocation(shader.getProgramIndex(), "fogParams.iEquation");
	glUniform1i(loc, fogParams.iEquation);

}