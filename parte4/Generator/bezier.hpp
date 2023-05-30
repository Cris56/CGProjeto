#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <sstream>
#include "geometry.hpp"
using namespace std;

void genBezier(float* v);
void verticesBezier();
void readPatch(const char* filename);
int numvtBezier(int tess);
float castjau(float* points, float ratio, int nump);
void curvePoints(Point* points, Point* v, int patch);