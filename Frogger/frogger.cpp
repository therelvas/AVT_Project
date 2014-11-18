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

//Scenario
#include "riverMargin.h"
#include "roadMargin.h"
#include "river.h"
#include "road.h"
#include "tree.h"

#include "frog.h"
#include "camera.h"
#include "light.h"
#include "fog.h"

#include "obstacles.h"

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

//level of speed of the game
float level = 1.0f;

//Objects
Frog *frog;
Light *light;

RoadMargin *roadMargin;
RiverMargin *riverMargin1;
RiverMargin *riverMargin2;

Road *road;
Tree *tree;
River *river;

Fog *fog;
Obstacles *obstacles;

//Camera
Camera *camera;
int view = 1;

//Spot ligths settings
float spotLight1[4] = { 5.0f, 6.0f, 4.0f, 1.0f };
float spotLight2[4] = { 13.0f, 6.0f, 16.0f, 1.0f };
float spotLight3[4] = { 5.0f, 6.0f, 36.0f, 1.0f };
float spotLight4[4] = { 13.0f, 6.0f, 56.0f, 1.0f };
float spotLight5[4] = { 5.0f, 6.0f, 76.0f, 1.0f };
float spotLight6[4] = { 13.0f, 6.0f, 96.0f, 1.0f };

float spotDir[4] = { 0.0f, -1.0f, 0.0f, 0.0f };

//Directional light
float dirLight[4] = { 0.0f, 10.0f, 0.0f, 0.0f };

//Frog spotlight
float frogSpotLight[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float frogSpotDir[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

// ------------------------------------------------------------
//
// Render stufff
//

void renderScene(void) {

	camera->draw(camX, camY, camZ, frog->getPosition()[0], frog->getPosition()[1], frog->getPosition()[2]);

	//Use our shader
	glUseProgram(shader.getProgramIndex());

	float currentSpotLight[4] = { frog->getPosition()[0], 6.0f, frog->getPosition()[2], 1.0f };
	float currentSpotDir[4] = { 5.0f, -6.0f, 0.0f, 0.0f };

	//Update frog spotlight position
	light->updateSpotPosDir(7, currentSpotLight, currentSpotDir);

	//Render light
	light->draw(shader);

	//reder fog
	fog->draw(shader);

	//Render obstacles
	obstacles->render(shader);

	//Render scenario objects
	roadMargin->render(shader);
	road->render(shader);

	riverMargin1->render(shader);
	riverMargin2->render(shader);

	frog->render(shader);

	tree->updateRotation(frog->getPosition());
	tree->render(shader);

	//Planar reflection and stencil buffer
	glEnable(GL_STENCIL_TEST);

	// Draw river
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF); // Write to stencil buffer
	glDepthMask(GL_FALSE); // Don't write to depth buffer
	glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)
	river->render(shader);

	// Draw frog reflection
	glDepthMask(GL_TRUE); // Write to depth buffer
	glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
	glStencilMask(0x00); // Don't write anything to stencil buffer
	glDepthMask(GL_TRUE); // Write to depth buffer
	frog->renderReflection(shader);

	glDisable(GL_STENCIL_TEST);
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

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;

	WinX = w;
	WinY = h;

	glViewport(0, 0, WinX, WinY);
	camera = new Camera(w, h, view);
}

void timer(int value) {

	std::ostringstream oss;

	if (frog->getLives() == 0)
		oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")" << " GAME OVER " << " Points: " << frog->getPoints();
	else
		oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")" << " Lives: " << frog->getLives() << " Points: " << frog->getPoints();

	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
	FrameCount = 0;

	//Speeds up the game with the passing of time
	level += 0.05f;
	obstacles->setLevel(level);

	glutTimerFunc(1000, timer, 0);
}

//Generate enemies
void updateEnemies(int value) {

	obstacles->updatePosition();
	obstacles->destroyObstacles();

	glutPostRedisplay();
	glutTimerFunc(1000/ 60, updateEnemies, 0);
}

// ------------------------------------------------------------
//
// Events from the Keyboard
//

void processKeys(unsigned char key, int xx, int yy) {
	
	if (key == 'r' && frog->getLives() == 0){
		frog->resetLives();
		return;
	}

	if (frog->getLives() > 0) {

		switch (key) {

		case 27:
			glutLeaveMainLoop();
			break;
		case 'a':
			frog->move(-0.5f, 0.0f, 0.0f, 1.5f);
			break;
		case 'q':
			frog->move(0.5f, 0.0f, 0.0f, 1.5f);
			break;
		case 'o':
			frog->move(0.0f, 0.0f, -0.5f, 2.0f);
			break;
		case 'p':
			frog->move(0.0f, 0.0f, 0.5f, 2.0f);
			break;
		case 's':
			level = 1.0f;
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
		case 'n':
			light->switchLight(0);
			light->switchLight(7);
			break;
		case 'c':
			light->switchLight(1);
			light->switchLight(2);
			light->switchLight(3);
			light->switchLight(4);
			light->switchLight(5);
			light->switchLight(6);
			break;
		case 'f':{
			if (fog->fogParams.isEnabled)
				fog->fogParams.isEnabled = false;
			else
				fog->fogParams.isEnabled = true;
		}
			break;
		}
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
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/multiplelights.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/multiplelights.frag");

	// set semantics for the shader variables
	glBindFragDataLocation(shader.getProgramIndex(), 0, "colorOut");
	glBindAttribLocation(shader.getProgramIndex(), VSShaderLib::VERTEX_COORD_ATTRIB, "vertexPosition");
	glBindAttribLocation(shader.getProgramIndex(), VSShaderLib::NORMAL_ATTRIB, "vertexNormal");
	glBindAttribLocation(shader.getProgramIndex(), VSShaderLib::TEXTURE_COORD_ATTRIB, "vertexTexCoord");

	// add sampler uniform
	GLint loc = glGetAttribLocation(shader.getProgramIndex(), "texUnit");
	glUniform1i(loc, 0);

	glLinkProgram(shader.getProgramIndex());

	printf("Shader Infolog\n%s\n\n", shader.getAllInfoLogs().c_str());

	return(shader.isProgramValid());
}


// --------------------------------------------------------
//
// Object creation
//

void setupObjects() {

	light = new Light();
	fog = new Fog();
	frog = new Frog(0.0f, 0.0f, 50.0f);

	roadMargin = new RoadMargin(0.0f, -1.5f, 0.0f);
	riverMargin1 = new RiverMargin(RIVER_MARGIN1_X, -1.5f, 0.0f);
	riverMargin2 = new RiverMargin(RIVER_MARGIN2_X, -1.5f, 0.0f);

	tree = new Tree(30.0f, -0.5f, 50.0f);
	road = new Road(ROAD_X, -1.5f, 0.0f);
	river = new River(RIVER_X, -1.5f, 0.0f);

	obstacles = new Obstacles(frog);

	//Setup lights
	light->addLight(Light::DIRECTIONAL, dirLight, 0, 0, 0);

	light->addLight(Light::SPOT, spotLight1, spotDir, 0.90f, 1);
	light->addLight(Light::SPOT, spotLight2, spotDir, 0.90f, 2);
	light->addLight(Light::SPOT, spotLight3, spotDir, 0.90f, 3);
	light->addLight(Light::SPOT, spotLight4, spotDir, 0.90f, 4);
	light->addLight(Light::SPOT, spotLight5, spotDir, 0.90f, 5);
	light->addLight(Light::SPOT, spotLight6, spotDir, 0.90f, 6);

	light->addLight(Light::SPOT, frogSpotLight, frogSpotDir, 0.90f, 7);
}


// ------------------------------------------------------------
//
// General setup
//

void setupCallbacks()
{
	//  Callback Registration
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);

	//	Mouse and Keyboard Callbacks
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	glutMouseWheelFunc(mouseWheel);

	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, updateEnemies, 0);
}


void setupOpenGL()
{
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

