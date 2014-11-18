#ifndef SURFACE_H
#define SURFACE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "lib/vsShaderLib.h"
#include "lib/vsMathLib.h"
#include "lib/vsResourceLib.h"

#include "constants.h"

class Surface {

private:

	GLuint vao;
	VSMathLib *vsml;

	int faceCount = 2;

	GLuint texUnits[MAX_TEXTURES];
	GLuint texTypes[MAX_TEXTURES];

	struct Material{

		float diffuse[4];
		float ambient[4];
		float specular[4];
		float emissive[4];
		float shininess;
		int texCount;
	} mat;

public:

	Surface();
	~Surface();

	void setupObjects();
	void setColor(VSResourceLib::MaterialSemantics mSemantics, float* values);
	void setMaterial(VSShaderLib shader);
	unsigned int loadRGBATexture(std::string filename, bool mipmap = true,
		bool compress = false,
		GLenum aFilter = GL_LINEAR, GLenum aRepMode = GL_REPEAT);
	void addTexture(unsigned int unit, std::string filename);
	void render(VSShaderLib shader);
};

#endif