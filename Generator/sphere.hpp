#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "geometry.hpp"
using namespace std;

void genSphere(float radius, int slices, int stacks, float *v);
void verticesSphere(float radius, int slices, int stacks);
