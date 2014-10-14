#include <math.h>
#include <iostream>
#include <sstream>
#include <string>

// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>

// Use Very Simple Libs
#include "lib/VSShaderlib.h"
#include "lib/vsMathLib.h"
#include "lib/vsResSurfRevLib.h"

//
#include "Scenario.h"
#include "Frog.h"
#include "Car.h"
#include "camera.h"
#include "Turtle.h"
#include "Wood.h"

#define CAPTION "Frogger"

int WindowHandle = 0;
int WinX = 640, WinY = 480;

unsigned int FrameCount = 0;

VSMathLib *vsml;
VSShaderLib shader;

// Camera Position
float camX, camY, camZ;

// Mouse Tracking Variables
int startX, startY, tracking = 0;

// Camera Spherical Coordinates
float alpha = 39.0f, beta = 51.0f;
float r = 10.0f;

//Light position
float lightPos[4] = { 20.0f, 50.0f, 0.0f, 1.0f };

//Objects
Scenario *scenario;
Frog *frog;
Car *enemy;
Turtle *turtle;
Wood* wood;


//Camera
Camera *camera;
int view = 1;

// ------------------------------------------------------------
//
// Render stufff
//

void renderScene(void) {

	camera->draw(camX, camY, camZ, frog->getActualPostion()[0], frog->getActualPostion()[1], frog->getActualPostion()[2]);

	// use our shader
	glUseProgram(shader.getProgramIndex());

	//send the light position in eye coordinates
	float res[4];
	vsml->multMatrixPoint(VSMathLib::VIEW, lightPos, res);   //lightPos defined in World Coord so is converted to eye space
	GLint lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "l_pos");
	glUniform4fv(lPos_uniformId, 1, res);

	//render objects
	frog->render(shader);
	scenario->render(shader);
	enemy->render(shader);
	turtle->render(shader);
	wood->render(shader);
}

// ------------------------------------------------------------
//
// Callback function
//

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderScene();
	glutSwapBuffers();
}


void idle()
{
	glutPostRedisplay();
}


void changeSize(int w, int h) {

	if (h == 0)
		h = 1;

	WinX = w;
	WinY = h;

	glViewport(0, 0, WinX, WinY);
	camera = new Camera(w, h, view);
}


void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
	FrameCount = 0;
	glutTimerFunc(1000, timer, 0);
}


// ------------------------------------------------------------
//
// Events from the Keyboard
//

void processKeys(unsigned char key, int xx, int yy)
{
	switch (key) {

	case 27:
		glutLeaveMainLoop();
		break;
	case 'c':
		printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
		break;
	case 'a':
		frog->moveToBack();
		break;
	case 'q':
		frog->moveToFront();
		break;
	case 'o':
		frog->moveToLeft();
		break;
	case 'p':
		frog->moveToRight();
		break;
	case '1':
		camera->setView(1);
		view = 1;
		break;
	case '2':
		camera->setView(2);
		view = 2;
		break;
	case '3':
		camera->setView(3);
		view = 3;
		break;
	case '4':
		camera->setView(4);
		view = 4;
		break;
	}
}


// ------------------------------------------------------------
//
// Mouse Events
//

void processMouseButtons(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha -= (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
			if (r < 0.1f)
				r = 0.1f;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy)
{

	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX = -xx + startX;
	deltaY = yy - startY;

	// left mouse button: move camera
	if (tracking == 1) {

		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0f)
			betaAux = 85.0f;
		else if (betaAux < -85.0f)
			betaAux = -85.0f;
		rAux = r;
	}
	// right mouse button: zoom
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r + (deltaY * 0.01f);
		if (rAux < 0.1f)
			rAux = 0.1f;
	}

	camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camY = rAux *   						       sin(betaAux * 3.14f / 180.0f);
}


void mouseWheel(int wheel, int direction, int x, int y) {

	r += direction * 0.1f;
	if (r < 0.1f)
		r = 0.1f;

	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);
}


// --------------------------------------------------------
//
// Shader Stuff
//

GLuint setupShaders() {

	vsml = VSMathLib::getInstance();

	// Shader for models
	shader.init();
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");

	// set semantics for the shader variables
	glBindFragDataLocation(shader.getProgramIndex(), 0, "colorOut");
	glBindAttribLocation(shader.getProgramIndex(), VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	glBindAttribLocation(shader.getProgramIndex(), VSShaderLib::NORMAL_ATTRIB, "normal");
	glBindAttribLocation(shader.getProgramIndex(), VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");

	glLinkProgram(shader.getProgramIndex());

	printf("InfoLog for Hello World Shader\n%s\n\n", shader.getAllInfoLogs().c_str());

	return(shader.isProgramValid());
}


// --------------------------------------------------------
//
// Object creation
//

void setupObjects() {

	frog = new Frog(0,0,50);
	scenario = new Scenario();
	enemy = new Car(true, 3, 0.5, 0);
	turtle = new Turtle(true, 15, 0.5, 0);
	wood = new Wood(true, 20, 0.5, 0);
}


// ------------------------------------------------------------
//
// General setup
//

void setupCallbacks()
{
	//  Callback Registration
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(changeSize);

	//	Mouse and Keyboard Callbacks
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	glutMouseWheelFunc(mouseWheel);

	glutTimerFunc(0, timer, 0);
}


void setupOpenGL()
{
	// set the camera position based on its spherical coordinates
	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);

	// set the camera position based on its spherical coordinates
	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);

	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}


void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}


void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 1);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(CAPTION);
	if (WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}


int init(int argc, char **argv) {

	setupGLUT(argc, argv);
	setupGLEW();
	setupCallbacks();
	setupShaders();
	setupObjects();
	setupOpenGL();

	return(0);
}


int main(int argc, char *argv[]) {

	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

