#include "engine.hpp"

World world;

World convertToWorld(char* file) {

    World world;

    xml_document doc;
    xml_parse_result result = doc.load_file(file, parse_default, encoding_auto);
    std::cout << "XML [" << file << "] parsed with result [" << result.description() << "]\n";
    // Access the window element
    pugi::xml_node window_node = doc.child("world").child("window");
    world.width = window_node.attribute("width").as_int();
    world.height = window_node.attribute("height").as_int();
    
    // Access the camera position, lookAt, up, and projection elements
    pugi::xml_node position_node = doc.child("world").child("camera").child("position");
    world.camera.position.x = position_node.attribute("x").as_float();
    world.camera.position.y = position_node.attribute("y").as_float();
    world.camera.position.z = position_node.attribute("z").as_float();
    
    pugi::xml_node lookAt_node = doc.child("world").child("camera").child("lookAt");
    world.camera.lookAt.x = lookAt_node.attribute("x").as_float();
    world.camera.lookAt.y = lookAt_node.attribute("y").as_float();
    world.camera.lookAt.z = lookAt_node.attribute("z").as_float();

    pugi::xml_node up_node = doc.child("world").child("camera").child("up");
    world.camera.up.x = up_node.attribute("x").as_float();
    world.camera.up.y = up_node.attribute("y").as_float();
    world.camera.up.z = up_node.attribute("z").as_float();
   
    pugi::xml_node projection_node = doc.child("world").child("camera").child("projection");
    world.camera.fov = projection_node.attribute("fov").as_float();
    world.camera.near = projection_node.attribute("near").as_float();
    world.camera.far = projection_node.attribute("far").as_float();

    pugi::xml_node group_node = doc.child("world").child("group");
    world.group = convertGroup(group_node);
    return world;
}

Group convertGroup(pugi::xml_node group_node) {
    Group group;

    for (pugi::xml_node child : group_node.children()) {
        if (std::string(child.name()) == "group") {
            group.groups.push_back(convertGroup(child));

        } else if (std::string(child.name()) == "transform") {

            Transform transform;

            pugi::xml_node translate = group_node.child("transform").child("translate");
            transform.translation.x = translate.attribute("x").as_float();
            transform.translation.y = translate.attribute("y").as_float();
            transform.translation.z = translate.attribute("z").as_float();

            pugi::xml_node rotate = group_node.child("transform").child("rotate");
            transform.rotation.x = rotate.attribute("x").as_float();
            transform.rotation.y = rotate.attribute("y").as_float();
            transform.rotation.z = rotate.attribute("z").as_float();
            transform.rotation.angle = rotate.attribute("angle").as_float();

            pugi::xml_node scale = group_node.child("transform").child("scale");
            transform.scale.x = scale.attribute("x").as_float();
            transform.scale.y = scale.attribute("y").as_float();
            transform.scale.z = scale.attribute("z").as_float();
            
            group.transforms.push_back(transform);

        } else if (std::string(child.name()) == "models") {
            for (pugi::xml_node model_node : child.children()) {
                Model model;
                model.file = model_node.attribute("file").as_string();
                group.models.push_back(model);
            }
        }
    }
    return group;
}

void print_world(World world) {
    std::cout << "Window: width=" << world.width
                    << ", height=" << world.height << std::endl;

    std::cout << "Position: x=" << world.camera.position.x
                      << ", y=" << world.camera.position.y
                      << ", z=" << world.camera.position.z << std::endl;

    std::cout << "LookAt: x=" << world.camera.lookAt.x
                    << ", y=" << world.camera.lookAt.y
                    << ", z=" << world.camera.lookAt.z << std::endl;

    std::cout << "Up: x=" << world.camera.up.x
                << ", y=" << world.camera.up.y
                << ", z=" << world.camera.up.z << std::endl;

    std::cout << "Projection: fov=" << world.camera.fov
                        << ", near=" << world.camera.near
                        << ", far=" << world.camera.far << std::endl;

    
    std::cout << "Group" << std::endl;
    printGroup(world.group, 1);
}

void printGroup(Group group, int indentLevel) {

    std::string indent(indentLevel * 2, ' ');

    for(Transform transform : group.transforms) {
        std::cout << indent << "Transform: translate=(" << transform.translation.x
                  << ", " << transform.translation.y
                  << ", " << transform.translation.z
                  << ")" << std::endl;

        std::cout << indent << "Transform: rotate=(" << transform.rotation.x
                  << ", " << transform.rotation.y
                  << ", " << transform.rotation.z
                  << "), angle=" << transform.rotation.angle << std::endl;

        std::cout << indent << "Transform: scale=(" << transform.scale.x
                  << ", " << transform.scale.y
                  << ", " << transform.scale.z << ")" << std::endl;
    }

    for(Model model : group.models) {
        std::cout << indent << "Model: " << model.file << std::endl;
    }

    for(Group group : group.groups) {
        std::cout << indent << "Group" << std::endl;
        printGroup(group, indentLevel + 1);
    }

    return;
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
	gluLookAt(world.camera.position.x, world.camera.position.y, world.camera.position.z,
		      world.camera.lookAt.x, world.camera.lookAt.y, world.camera.lookAt.z,
              world.camera.up.x, world.camera.up.y, world.camera.up.z);

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

    world = convertToWorld(str);

    print_world(world);

    // GLUT init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(world.width, world.height);
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