#ifndef CAMERA_H
#define CAMERA_H

// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>

// Use Very Simple Libs
#include "lib/VSMathlib.h"

#define ORTHO 30

class Camera {

private:

	int view;
	int width;
	int height;
	float ratio;
	VSMathLib *vsml;

public:

	Camera(int w, int h, int v);
	~Camera(void);

	void draw(float x, float y, float z);
	int getView(void);
	void setView(int view);
};

#endif