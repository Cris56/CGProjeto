#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "geometry.hpp"
using namespace std;

void genTexPlane(Point* points, int div, float size, Point* dest);
void genTexBox(Point* points, float size, int div, Point* dest);
void genTexSphere(int slices, int stacks, Point* dest);
void genTexBezier(int tess, int patches, Point* dest);
void genTexCone(int slices, int stacks, Point* dest);
