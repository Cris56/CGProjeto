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
using namespace std;
using namespace pugi;

struct WorldInfo {
    int window_w;
    int window_h;
    float campos[3];
    float camlook[3];
    float camup[3];
    float camproj[3];
    std::vector<std::string> models;
};

WorldInfo lerXML(char* file);
void changeSize(int w, int h);
void renderScene(void);
void printWorldInfo(const WorldInfo& world_info);
