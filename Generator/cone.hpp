#include <math.h>
#include "geometry.hpp"

void genCone(float coneRadius, float coneHeight, int numSlices, int numStacks, float* v);
vector<triangle> genConeBase(float coneRadius, int numSlices, int numStacks);
vector<triangle> genConeBody(float radius, float height, int slices, int stacks);
