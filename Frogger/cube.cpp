#include "cube.h"
#include "cubeData.h"

Cube::Cube() {

	vsml = VSMathLib::getInstance();
	setupObjects();
}

Cube::~Cube(){}

void Cube::setupObjects() {

	// create the VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create buffers for our vertex data
	GLuint buffers[4];
	glGenBuffers(4, buffers);

	//vertex coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);

	//normals buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::NORMAL_ATTRIB);
	glVertexAttribPointer(VSShaderLib::NORMAL_ATTRIB, 3, GL_FLOAT, 0, 0, 0);


	//texture coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, 0, 0, 0);

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faceIndex), faceIndex, GL_STATIC_DRAW);

	//unbind the VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
	glDisableVertexAttribArray(VSShaderLib::NORMAL_ATTRIB);
	glDisableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
}


void Cube::setColor(VSResourceLib::MaterialSemantics mSemantics, float *values) {

	GLint loc;

	switch (mSemantics) {
		case VSResourceLib::DIFFUSE:
			memcpy(mat.diffuse, values, sizeof(float)* 4);
			break;
		case VSResourceLib::AMBIENT:
			memcpy(mat.ambient, values, sizeof(float)* 4);
			break;
		case VSResourceLib::SPECULAR:
			memcpy(mat.specular, values, sizeof(float)* 4);
			break;
		case VSResourceLib::EMISSIVE:
			memcpy(mat.emissive, values, sizeof(float)* 4);
			break;
		case VSResourceLib::SHININESS:
			mat.shininess = *values;
			break;
		case VSResourceLib::TEX_COUNT:
			break;
	}
}

void Cube::setMaterial(VSShaderLib shader) {

	GLint loc;

	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.ambient");
	glUniform4fv(loc, 1, mat.ambient);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.diffuse");
	glUniform4fv(loc, 1, mat.diffuse);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.specular");
	glUniform4fv(loc, 1, mat.specular);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.shininess");
	glUniform1f(loc, mat.shininess);
	loc = glGetUniformLocation(shader.getProgramIndex(), "mat.emissive");
	glUniform4fv(loc, 1, mat.emissive);
}


void Cube::render(VSShaderLib shader) {

	//Send matrices to GL
	vsml->matricesToGL(shader);

	//Set material
	setMaterial(shader);

	// render VAO
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}