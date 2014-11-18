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

unsigned int Cube::loadRGBATexture(std::string filename,
											bool mipmap, bool compress,
											GLenum aFilter, GLenum aRepMode) {

	ILboolean success;
	unsigned int imageID;
	GLuint textureID = 0;

	// Load Texture Map
	ilGenImages(1, &imageID);

	ilBindImage(imageID); /* Binding of DevIL image name */
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	success = ilLoadImage((ILstring)filename.c_str());

	/* Convert image to RGBA */
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	// Set filters
	GLenum minFilter = aFilter;
	if (aFilter == GL_LINEAR && mipmap) {
		minFilter = GL_LINEAR_MIPMAP_LINEAR;
	}
	else if (aFilter == GL_NEAREST && mipmap){
		minFilter = GL_NEAREST_MIPMAP_LINEAR;
	}
	GLenum type;
	if (compress)
		type = GL_RGBA;
	else
		type = GL_COMPRESSED_RGBA;


	/* Create and load textures to OpenGL */
	glGenTextures(1, &textureID); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, aFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, aRepMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, aRepMode);
	glTexImage2D(GL_TEXTURE_2D, 0, type,
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		ilGetData());

	// Mipmapping?
	if (mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	/* Because we have already copied image data into texture data
	we can release memory used by image. */
	ilDeleteImages(1, &imageID);

	return textureID;
}

void Cube::addTexture(unsigned int unit, std::string filename) {

	int textID = loadRGBATexture(filename, true);
	texUnits[unit] = textID;
	texTypes[unit] = GL_TEXTURE_2D;
	mat.texCount = 1;
}

void Cube::render(VSShaderLib shader) {

	//Send matrices to GL
	vsml->matricesToGL(shader);

	//Set material
	setMaterial(shader);

	// bind texture
	for (unsigned int j = 0; j < MAX_TEXTURES; ++j) {
		if (texUnits[j] != 0) {
			glActiveTexture(GL_TEXTURE0 + j);
			glBindTexture(texTypes[j], texUnits[j]);
		}
	}

	// render VAO
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	for (unsigned int j = 0; j < MAX_TEXTURES; ++j) {
		if (texUnits[j] != 0) {
			glActiveTexture(GL_TEXTURE0 + j);
			glBindTexture(texTypes[j], 0);
		}
	}
}