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

void genSphere(float radius, int slices, int stacks, float *v, float* vt);
void verticesSphere(float radius, int slices, int stacks);
