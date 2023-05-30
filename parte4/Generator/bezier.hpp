#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;

struct ponto { float ponto[3]; };

void genBezier(float* v);
void verticesBezier();
void readPatch(const char* filename);
int numvtBezier(int tess);
float castjau(float* points, float ratio, int nump);
void curvePoints(ponto* points, ponto* v, int patch);