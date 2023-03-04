#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#include "pugixml.hpp"

#include <iostream>
#include <fstream>
using namespace std;

int wwidth = 800;
int wheight = 800;

float campos[3] = { 0.0f,0.0f,5.0f };
float camlook[3] = { 0.0f,0.0f,-1.0f };
float camup[3] = { 0.0f,1.0f,0.0f };
float camproj[3] = { 45.0f,1.0f,1000.0f };

char *modelo;

void ler3D(char* file, char* buf) {
	char c;
	streampos size;
	ifstream fd(file,ios::ate);
	if (fd.is_open()) {
		size = fd.tellg();
		modelo = new char[size];
		fd.seekg(0, ios::beg);
		fd.read(modelo, size);
		fd.close();
	}
	else printf("Error opening file");
}

void lerXML(char* file) {

	ler3D("sphere.3d", modelo);
}

void changeSize(int w, int h) {
	// prevent a divide by zero, when window is too short
	// (you can not make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;

	// set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// load the identity matrix
	glLoadIdentity();
	// set the perspective
	gluPerspective(camproj[0], ratio, camproj[1], camproj[2]);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// set the viewport to be the entire window
	glViewport(0, 0, w, h);
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set camera
	glLoadIdentity();
	gluLookAt(campos[0], campos[1], campos[2],
		camlook[0], camlook[1], camlook[2],
		camup[0], camup[1], camup[2]);

	// drawing instructions
	glutWireTeapot(1);

	// end of frame
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	lerXML("teste_1_3.xml");
	// GLUT init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(wwidth, wheight);
	glutCreateWindow("CG@DI-UM");

	// callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// enter GLUTs main cycle
	glutMainLoop();

	return 1;
}
