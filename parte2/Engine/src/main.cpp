#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>

#else
#include <GL/glut.h>
#endif

#include "World.hpp"
#include "XMLParser.hpp"
#include <iostream>
#include <math.h>

World world;

double r;
double theta;
double phi;

void drawModels();
void changeSize(int w, int h);
void renderScene(void);
void renderGroups(Group group);
void keyboard(unsigned char key, int x, int y);

void drawModels() {

	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,-100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f,-100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
		
	glColor3f(1.0f, 1.0f, 1.0f);

	renderGroups(world.getGroup());
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
	gluPerspective(60, ratio, 1, 1000);
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

	gluLookAt(r * sin(theta) * cos(phi),r * sin(phi), r * cos(theta) * cos(phi),
		      world.getCamera().getLookAt().getX(), world.getCamera().getLookAt().getY(), world.getCamera().getLookAt().getZ(),
              world.getCamera().getUp().getX(), world.getCamera().getUp().getY(), world.getCamera().getUp().getZ());

	// drawing instructions
	drawModels();

	// end of frame
	glutSwapBuffers();
}

void renderGroups(Group group) {
	
	Transform transform = group.getTransform();
	std::vector<TransformType> transformOrder = transform.getTransformationOrder();

	for (size_t j = 0; j < transformOrder.size(); j++) {
		TransformType type = transformOrder[j];
		switch(type) {
			case TRANSLATION:
				glTranslatef(transform.getTranslation().getX(), transform.getTranslation().getY(), transform.getTranslation().getZ());
				break;
			case ROTATION:
				glRotatef(transform.getRotationAngle(), transform.getRotation().getX(), transform.getRotation().getY(), transform.getRotation().getZ());
				break;
			case SCALING:
				glScalef(transform.getScale().getX(), transform.getScale().getY(), transform.getScale().getZ());
				break;
		}
	}
	
	glBegin(GL_TRIANGLES);
	
	for(size_t i = 0; i < group.models.size(); i++) {
		Model model = group.models[i];
		for(size_t j = 0; j < model.getVertices().size(); j++) {
			Vector3 vertices = model.getVertices()[j];
			glVertex3f(vertices.getX(), vertices.getY(), vertices.getZ());
		}
	}
	
	glEnd();

	for (size_t i = 0; i < group.groups.size(); i++) {
		Group childGroup = group.groups[i];
		glPushMatrix();
		renderGroups(childGroup);
		glPopMatrix();
	}
	
}

// write function to process keyboard events
void keyboard(unsigned char key, int x, int y) {
	switch (toupper(key))
	{
	case 'W':
		phi += 0.1f;
		if (phi > 1.5f)
			phi = 1.5f;
		glutPostRedisplay();
		break;
	case 'S':
		phi -= 0.1f;
		if (phi < -1.5f)
			phi = -1.5f;
		glutPostRedisplay();
		break;
	case 'A':
		theta -= 0.1f;
		glutPostRedisplay();
		break;
	case 'D':
		theta += 0.1f;
		glutPostRedisplay();
		break;
	case 'Q':
		r += 5.0f;
		glutPostRedisplay();
		break;
	case 'E':
		r -= 5.0f;
		glutPostRedisplay();
		break;
	default:
		break;
	};
}

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s <file name>\n", argv[0]);
        return 1;
    }
    
    world = convertToWorld(argv[1]);

	float x = world.getCamera().getPosition().getX();
	float y = world.getCamera().getPosition().getY();
	float z = world.getCamera().getPosition().getZ();

	r = sqrt(x*x + y*y + z*z);
	theta = atan2(sqrt(x * x + y * y), z);
	phi = atan2(y, x);

	// GLUT init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(world.getWidth(), world.getHeight());
	glutCreateWindow("CG@DI-UM Grupo 7");

	// callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(keyboard);

	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// enter GLUTs main cycle
	glutMainLoop();

    return 0;
}
