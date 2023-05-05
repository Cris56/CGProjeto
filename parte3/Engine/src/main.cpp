#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GL/glut.h>

#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "world.hpp"
#include "xmlParser.hpp"
#include <iostream>
#include <math.h>
#include <vector>
#include "Curva_CATMR_H.hpp"

World world;
GLuint vertices, verticeCount;

void drawModels();
void changeSize(int w, int h);
void renderScene(void);
void renderGroups(const Group& group);
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

	//world.getCamera().getPosition().printCartesianCoordinates();
	world.getCamera().getPosition().printSphericalCoordinates();

	gluLookAt(world.getCamera().getPosition().getX(), world.getCamera().getPosition().getY(), world.getCamera().getPosition().getZ(),
		      world.getCamera().getLookAt().getX(), world.getCamera().getLookAt().getY(), world.getCamera().getLookAt().getZ(),
              world.getCamera().getUp().getX(), world.getCamera().getUp().getY(), world.getCamera().getUp().getZ());

	// drawing instructions
	drawModels();

	// end of frame
	glutSwapBuffers();
}

void renderGroups(const Group& group) {
	const Transform& transform = group.getTransform();
    const std::vector<TransformType>& transformOrder = transform.getTransformationOrder();

    for (size_t j = 0; j < transformOrder.size(); j++) {
        TransformType type = transformOrder[j];
        switch(type) {
            case TRANSLATION:
                glTranslatef(transform.getTranslation().getX(), transform.getTranslation().getY(), transform.getTranslation().getZ());
				break;
            case ROTATION:
                glRotatef(transform.getTimeForRotation(), transform.getRotation().getX(), transform.getRotation().getY(), transform.getRotation().getZ());
                break;
            case SCALING:
                glScalef(transform.getScale().getX(), transform.getScale().getY(), transform.getScale().getZ());
                break;
			case CURVE:
				drawTranslation(transform.getcurvepoints(),transform.getTime());
				break;
        }
    }

    // Generate and bind VBO
    std::vector<float> p;
    for(size_t i = 0; i < group.models.size(); i++) {
		const std::vector<float>& modelVBO = group.models[i].getVBO();
		p.insert(p.end(), modelVBO.begin(), modelVBO.end());

    }
    verticeCount = p.size() / 3;

    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(), p.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Draw models
    for(size_t i = 0; i < group.models.size(); i++) {
        glDrawArrays(GL_TRIANGLES, i * verticeCount / group.models.size(), verticeCount / group.models.size());

    }

    // Recursively render child groups
    for (size_t i = 0; i < group.groups.size(); i++) {
        Group childGroup = group.groups[i];
        glPushMatrix();
        renderGroups(childGroup);
        glPopMatrix();
    }

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &vertices);
}


// write function to process keyboard events
void keyboard(unsigned char key, int x, int y) {
	switch (toupper(key))
	{
	case 'W':
		world.incrementCameraPositionbetaAngle(0.1f);
		break;
	case 'S':
		world.incrementCameraPositionbetaAngle(-0.1f);
		break;
	case 'A':
		world.incrementCameraPositionalphaAngle(-0.1f);
		break;
	case 'D':
		world.incrementCameraPositionalphaAngle(0.1f);
		break;
	case 'Q':
		world.incrementCameraPositionRadius(5.0f);
		break;
	case 'E':
		world.incrementCameraPositionRadius(-5.0f);
		break;
	default:
		break;
	};
	glutPostRedisplay();
}




void getCurvePoint(std::vector<Point> c, float tt, float* pos, float* deriv) {
		int conta = c.size();
		
		float t = tt * conta;
		int index = static_cast<int>(floor(t));
		t = t - index;


		int indices[4];
		indices[0] = (index + conta - 1) % conta;
		indices[1] = (indices[0] + 1) % conta;
		indices[2] = (indices[1] + 1) % conta;
		indices[3] = (indices[2] + 1) % conta;

		float p[4][3];
		for (int i = 0; i < 4; i++) {
			p[i][0] = c.at(indices[i]).getX();
			p[i][1] = c.at(indices[i]).getY();
			p[i][2] = c.at(indices[i]).getZ();
			//printf("aqui x z %f %f\n", (trans->pontos->at(indices[i]))->x, (trans->pontos->at(indices[i]))->z);
		}
		CMRPoint(t, p[0], p[1], p[2], p[3], pos, deriv);
	}




void drawTranslation(std::vector<Point> t,int timestp) {
		float pos[3];
		float deriv[3];

		float scaledT = glutGet(GLUT_ELAPSED_TIME) / timestp;
		float tmp2 = 5.0f;
		float tmp1 = glutGet(GLUT_ELAPSED_TIME) / tmp2;

		getCurvePoint(t, scaledT, (float*)pos, (float*)deriv);
		glTranslatef(pos[0], pos[1], pos[2]);
		normaliza((float*)deriv);
		Point p = Point(0,1,0);
		float z[3];
		ProdVet((float*)deriv,reinterpret_cast<float*>(&p),(float*)z);
		normaliza((float*)z);
	
		ProdVet((float*)z, (float*)deriv, reinterpret_cast<float*>(&p));
		normaliza(reinterpret_cast<float*>(&p));

		float rotateMatrix[4][4];
		makeMatrix((float*)deriv, reinterpret_cast<float*>(&p), (float*)z, (float*)rotateMatrix);

		glMultMatrixf((float*)rotateMatrix);

	}




int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s <file name>\n", argv[0]);
        return 1;
    }
    
    world = convertToWorld(argv[1]);

	// GLUT init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(world.getWidth(), world.getHeight());
	glutCreateWindow("CG@DI-UM Grupo 7");

	// GLEW init
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		exit(1);
	}

	glEnableClientState(GL_VERTEX_ARRAY);

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
