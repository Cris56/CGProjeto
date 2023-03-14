#include "engine.hpp"

WorldInfo world_info;
int nummodelos = 0;

void printWorldInfo(const WorldInfo& world_info) {
    std::cout << "Window width: " << world_info.window_w << "\nWindow height: " << world_info.window_h << "\n\n";
    std::cout << "Position: " << world_info.campos[0] << " " << world_info.campos[1] << " " << world_info.campos[2] << "\n";
    std::cout << "LookAt: " << world_info.camlook[0] << " " << world_info.camlook[1] << " " << world_info.camlook[2] << "\n";
    std::cout << "Up: " << world_info.camup[0] << " " << world_info.camup[1] << " " << world_info.camup[2] << "\n";
    std::cout << "Projection: " << world_info.camproj[0] << " " << world_info.camproj[1] << " " << world_info.camproj[2] << "\n\n";

    std::cout << "Models:\n";
    for (const auto& model : world_info.models) {
        std::cout << model << "\n";
		nummodelos++;
    }
}

WorldInfo lerXML(char* file) {
    WorldInfo world_info;

    xml_document f;
    xml_parse_result result = f.load_file(file, parse_default, encoding_auto);

    xml_node window = f.child("world").child("window");
    world_info.window_w = window.attribute("width").as_int();
    world_info.window_h = window.attribute("height").as_int();

    xml_node cam = f.child("world").child("camera");
    xml_node pos = cam.child("position");
    world_info.campos[0] = pos.attribute("x").as_float();
    world_info.campos[1] = pos.attribute("y").as_float();
    world_info.campos[2] = pos.attribute("z").as_float();

    xml_node look = cam.child("lookAt");
    world_info.camlook[0] = look.attribute("x").as_float();
    world_info.camlook[1] = look.attribute("y").as_float();
    world_info.camlook[2] = look.attribute("z").as_float();

    xml_node up = cam.child("up");
    world_info.camup[0] = up.attribute("x").as_float();
    world_info.camup[1] = up.attribute("y").as_float();
    world_info.camup[2] = up.attribute("z").as_float();

    xml_node proj = cam.child("projection");
    world_info.camproj[0] = proj.attribute("fov").as_float();
    world_info.camproj[1] = proj.attribute("near").as_float();
    world_info.camproj[2] = proj.attribute("far").as_float();

    xml_node models = f.child("world").child("group").child("models");
    for (xml_node model = models.child("model"); model; model = model.next_sibling("model")) {
        world_info.models.push_back(model.attribute("file").value());
    }

    return world_info;
}

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
	glBegin(GL_TRIANGLES);
	for (int a = 0; a < nummodelos; a++) {
		string model = world_info.models[a];
        string filepath = "../../data/" + model;
		ifstream modelfile(filepath);
		if (!modelfile) {
			throw runtime_error("Error opening file");
		}
		string m;
		getline(modelfile, m);
		int numvt = 3 * atoi(m.data());
		float * v = (float*) malloc(sizeof(float)*numvt*3);
		int i = 0;
		while (getline(modelfile, m)) {
			istringstream in(m);
			float x, y, z;
			in >> x >> y >> z;
			v[i] = x;
			v[i + 1] = y;
			v[i + 2] = z;
			i += 3;
			in.clear();
		}
		modelfile.close();
		for (int i = 0; i < numvt; i += 3) {
			glVertex3f(v[i], v[i + 1], v[i + 2]);
		}
		modelfile.clear();
		free(v);
	}
	glEnd();
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
	gluPerspective(world_info.camproj[0], ratio, world_info.camproj[1], world_info.camproj[2]);
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
	gluLookAt(world_info.campos[0], world_info.campos[1], world_info.campos[2],
		world_info.camlook[0], world_info.camlook[1], world_info.camlook[2],
		world_info.camup[0], world_info.camup[1], world_info.camup[2]);

	// drawing instructions
	drawModels();

	// end of frame
	glutSwapBuffers();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <file name>\n", argv[0]);
        return 1;
    }

    // Replace the file name in the array with the command-line argument
    char str[] = "../../data/";
    strcat(str, argv[1]);

    printf("Opening file: %s\n", str);
    
    world_info = lerXML(str);
    
    printWorldInfo(world_info);
	
    
	// GLUT init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(world_info.window_w, world_info.window_h);
	glutCreateWindow("CG@DI-UM Grupo 7");

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


