#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

struct ponto { float ponto[3]; };

void genSphere(float radius, int slices, int stacks, float *v);
void verticesSphere(float radius, int slices, int stacks);
