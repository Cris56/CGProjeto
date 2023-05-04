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

struct pontos { float ponto[3]; } ;

void genBezier(float* v);
void verticesBezier();
void readPatch(const char* filename);
int numvtBezier(int tess);
void curvePoints(pontos* points, pontos* v, int patch);
float castjau(float* points, float ratio, int nump);