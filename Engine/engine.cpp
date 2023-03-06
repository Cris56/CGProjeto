#include "engine.hpp"

int window_w = 800;
int window_h = 800;

float campos[3];
float camlook[3];
float camup[3];
float camproj[3];

vector<string> ms;

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
	lerXML("C:/Users/Utilizador/Desktop/CompGrafica/Trabalho/Engine/test_1_5.xml");
	// GLUT init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(window_w, window_h);
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

void lerXML(char* file) {
	xml_document f;
	xml_parse_result result = f.load_file(file, parse_default, encoding_auto);

	xml_node window = f.child("world").child("window");
	window_w = window.attribute("width").as_int();
	window_h = window.attribute("height").as_int();
	std::cout << "Window width: " << window_w << "\nWindow height: " << window_h << "\n\n";

	xml_node cam = f.child("world").child("camera");
	xml_node pos = cam.child("position");
	campos[0] = pos.attribute("x").as_float();
	campos[1] = pos.attribute("y").as_float();
	campos[2] = pos.attribute("z").as_float();
	std::cout << "Position: " << campos[0] << " " << campos[1] << " " << campos[2] << "\n";

	xml_node look = cam.child("lookAt");
	camlook[0] = look.attribute("x").as_float();
	camlook[1] = look.attribute("y").as_float();
	camlook[2] = look.attribute("z").as_float();
	std::cout << "LookAt: " << camlook[0] << " " << camlook[1] << " " << camlook[2] << "\n";

	xml_node up = cam.child("up");
	camup[0] = up.attribute("x").as_float();
	camup[1] = up.attribute("y").as_float();
	camup[2] = up.attribute("z").as_float();
	std::cout << "Up: " << camup[0] << " " << camup[1] << " " << camup[2] << "\n";

	xml_node proj = cam.child("projection");
	camproj[0] = proj.attribute("fov").as_float();
	camproj[1] = proj.attribute("near").as_float();
	camproj[2] = proj.attribute("far").as_float();
	std::cout << "Projection: " << camproj[0] << " " << camproj[1] << " " << camproj[2] << "\n\n";

	xml_node models = f.child("world").child("group").child("models");
	int i = 0;
	for (xml_node model = models.child("model"); model; model = model.next_sibling("model")) {
		i++;
		ms.resize(i);
		ms[i - 1] = model.attribute("file").value();
		std::cout << "Model: " << ms[i-1] << "\n";
	}
}