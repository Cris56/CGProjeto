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

struct WorldInfo {
    int window_w = 512;
    int window_h = 512;
    float campos[3] = { 3,2,1 };
    float camlook[3] = { 0,0,0 };
    float camup[3] = { 0,1,0 };
    float camproj[3] = { 60,1,1000 };
    std::vector<std::string> models;
};

WorldInfo lerXML(char* file);
void changeSize(int w, int h);
void renderScene(void);
void printWorldInfo(const WorldInfo& world_info);
void drawModels(); 
int getModelo(string filename, float *v);