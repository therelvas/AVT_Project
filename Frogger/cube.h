#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsShaderLib.h"
#include "lib/vsMathLib.h"

class Cube{

private:

	GLuint vao;
	VSMathLib *vsml;
	int verticeCount = 24;
	int faceCount = 12;

public:
	Cube();
	~Cube();
	
	void setupObjects();
	void render();
};

#endif