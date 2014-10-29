#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsShaderLib.h"
#include "lib/vsMathLib.h"
#include "lib/vsResourceLib.h"

class Cube {

private:

	GLuint vao;
	VSMathLib *vsml;

	int verticeCount = 24;
	int faceCount = 12;

	struct Material{

		float diffuse[4];
		float ambient[4];
		float specular[4];
		float emissive[4];
		float shininess;
		int texCount;
	} mat;

public:

	Cube();
	~Cube();
	
	void setupObjects();
	void setColor(VSResourceLib::MaterialSemantics mSemantics, float* values);
	void setMaterial(VSShaderLib shader);
	void render(VSShaderLib shader);
};

#endif