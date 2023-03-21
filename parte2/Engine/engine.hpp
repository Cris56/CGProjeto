#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>

#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "pugixml.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
using namespace std;
using namespace pugi;

struct Position {
    float x;
    float y;
    float z;
};

struct LookAt {
    float x;
    float y;
    float z;
};

struct Up {
    float x;
    float y;
    float z;
};

struct Camera {
    Position position;
    LookAt lookAt;
    Up up;
    float fov;
    float near;
    float far;
};

struct Model {
    std::string file;
};

struct Translation {
    float x;
    float y;
    float z;
};

struct Rotation {
    float x;
    float y;
    float z;
    float angle;
};

struct Scale {
    float x;
    float y;
    float z;
};

struct Transform {
    Translation translation;
    Rotation rotation;
    Scale scale;
};

struct Group {
    std::vector<Group> groups;
    std::vector<Model> models;
    std::vector<Transform> transforms;
};

struct World {
    int width;
    int height;
    Camera camera;
    Group group;
};

World lerXML(char* file);
void changeSize(int w, int h);
void renderScene(void);
void drawModels(); 
int getModelo(string filename, float *v);

World convertToWorld(pugi::xml_node doc);
Group convertGroup(pugi::xml_node group_node);
void print_world(World world);
void printGroup(Group group, int indentLevel);
