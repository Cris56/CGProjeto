#include "plane.hpp"

void genPlane(float x, float z, float *v) {
    
    // Ponto 1
    v[0] = x;
    v[1] = 0;
    v[2] = z;
    
    // Ponto 2
    v[3] = x;
    v[4] = 0;
    v[5] = -z;
    
    // Ponto 3
    v[6] = -x;
    v[7] = 0;
    v[8] = -z;
    
    // Ponto 4
    v[9] = -x;
    v[10] = 0;
    v[11] = z;
}
