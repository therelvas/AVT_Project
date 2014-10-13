#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

// include GLEW to access OpenGL 3.3 functions
#include <GL/glew.h>

// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>

//
#include "Scenario.h"
#include "Frog.h"
#include "Enemy.h"
#include "Camera.h"

// Use Very Simple Libs
#include "lib/vsMathLib.h"
#include "lib/vsShaderLib.h"
#include "lib/vsResSurfRevLib.h"

#define CAPTION "Frogger"

VSResSurfRevLib mySurfRes;
VSMathLib *vsml;
VSShaderLib shader, shaderF;

int WinX = 640, WinY = 320;
int WindowHandle = 0;
unsigned int FrameCount = 0;

// Camera Position
float camX, camY, camZ;

// Mouse Tracking Variables
int startX, startY, tracking = 0;

// Camera Spherical Coordinates
float alpha = -43.0f, beta = 48.0f;
float r = 5.25f;

//
Scenario *scenario;
Frog *frog;
Enemy *enemy;

//Camera
Camera *camera;
int view = 1;

//Light
float lightPos[4] = { 4.0f, 6.0f, 2.0f, 1.0f };

// ------------------------------------------------------------
//
// Render stuff
//

void renderScene(void) {

	camera->draw(camX, camY, camZ);

	float res[4];
	vsml->multMatrixPoint(VSMathLib::VIEW, lightPos, res);
	shader.setBlockUniform("Lights", "l_pos", res);

	glUseProgram(shader.getProgramIndex());
	
	frog->render();
	scenario->render();
	
	glUseProgram(0);
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

// Track mouse motion while buttons are pressed

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
	vsml->setUniformBlockName("Matrices");
	vsml->setUniformName(VSMathLib::PROJ_VIEW_MODEL, "m_pvm");
	vsml->setUniformName(VSMathLib::NORMAL, "m_normal");
	vsml->setUniformName(VSMathLib::VIEW_MODEL, "m_viewModel");

	// Shader for models
	shaderF.init();
	shaderF.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/color.vert");
	shaderF.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/color.frag");

	// set semantics for the shader variables
	shaderF.setProgramOutput(0, "outputF");
	shaderF.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shaderF.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");
	
	shaderF.prepareProgram();

	shaderF.setUniform("textUnit", 0);

	//
	shader.init();
	
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");

	shader.setProgramOutput(0, "outputF");
	shader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	shader.setVertexAttribName(VSShaderLib::NORMAL_ATTRIB, "normal");
	shader.setVertexAttribName(VSShaderLib::TEXTURE_COORD_ATTRIB, "texCoord");
	shader.prepareProgram();

	shader.setUniform("texUnit", 0);

	return(shader.isProgramValid());
}


// --------------------------------------------------------
//
// Object creation
//

void setupObjects() {

	frog = new Frog();
	scenario = new Scenario();
	enemy = new Enemy(); 
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