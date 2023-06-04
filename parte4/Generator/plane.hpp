#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "geometry.hpp"
#include "textures.hpp"
using namespace std;

void genPlane(float size, int divisions, float* v, float* vt);
void verticesPlano(float size, int divisions);
