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

void genBox(float length, int div, float* v, float* vt); 
void verticesBox(float length, int div);
