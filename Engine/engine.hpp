#ifdef __APPLE__
#include <GLUT/glut.h>
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


void lerXML(char* file);
void changeSize(int w, int h);
void renderScene(void);