///////////////////////////////////////////////////////////////////////
//
// 
// (c) 2014 by João Madeiras Pereira
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Test.h"
#include "lib\vsResSurfRevLib.h"
#include "lib\vsMathLib.h"
#include "lib\vsShaderLib.h"

#define CAPTION "Exercise 1"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

int WinX = 640, WinY = 320;
int WindowHandle = 0;
unsigned int FrameCount = 0;

VSShaderLib shader, shaderF;

GLuint VaoId, VboId[4];
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;

VSResSurfRevLib resSurfRevLib;
VSMathLib *mathLib;

/////////////////////////////////////////////////////////////////////// ERRORS

bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////////////// SHADERs

GLuint createShaderProgram()
{
	shaderF.init();
	shaderF.loadShader(VSShaderLib::VERTEX_SHADER, "Shaders/vertexShader2.vert");
	shaderF.loadShader(VSShaderLib::FRAGMENT_SHADER, "Shaders/fragmentShader2.frag");

	//shaderF.setProgramOutput(0, "outputF");
	//shaderF.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");
	
	shader.prepareProgram();

	checkOpenGLError("ERROR: Could not create shaders.");

	return(shader.isProgramValid());
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects()
{
	resSurfRevLib.createSphere(2.0f, 40);
}

void destroyBufferObjects(){}

/////////////////////////////////////////////////////////////////////// SCENE

void renderScene()
{
	mathLib->loadIdentity(VSMathLib::MatrixTypes::VIEW);
	mathLib->loadIdentity(VSMathLib::MatrixTypes::MODEL);
	mathLib->lookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);
	
	glUseProgram(ProgramId);
	
	resSurfRevLib.render();

	glUseProgram(0);
	
	checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	//destroyShaderProgram();
	destroyBufferObjects();
}

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

void reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);

	float ratio = (1.0f * w) / h;

	mathLib->loadIdentity(VSMathLib::PROJECTION);
	mathLib->perspective(45.00f, ratio, 1.0f, 100.0f);
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

/////////////////////////////////////////////////////////////////////// SETUP

void setupCallbacks()
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
}

void setupOpenGL() {
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

void init(int argc, char* argv[])
{
	//Setup external libraries
	mathLib = mathLib->getInstance();
	mathLib->setUniformBlockName("Matrices");
	mathLib->setUniformName(VSMathLib::PROJ_VIEW_MODEL, "pvm");

	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	createShaderProgram();
	createBufferObjects();
	setupCallbacks();
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////