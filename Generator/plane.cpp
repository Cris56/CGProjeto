#include "plane.hpp"

void genPlane(float size, int divisions, float *v) {
    int n = divisions;
    float step = size / divisions;
    float x = -size / 2.0f;
    float z = -size / 2.0f;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            v[3 * (n + 1) * i + 3 * j] = x + j * step;
            v[3 * (n + 1) * i + 3 * j + 1] = 0.0f;
            v[3 * (n + 1) * i + 3 * j + 2] = z + i * step;
        }
    }
}
