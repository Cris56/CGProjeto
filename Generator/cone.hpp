#include <math.h>
#include "geometry.hpp"

void genCone(float coneRadius, float coneHeight, int numSlices, int numStacks, float* v);
vector<Triangle> genConeBase(float coneRadius, int numSlices, int numStacks);
vector<Triangle> genConeBody(float radius, float height, int slices, int stacks);
