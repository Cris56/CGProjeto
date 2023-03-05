#include "sphere.hpp"

void genSphere(float radius, int slices, int stacks, float *v) {
    int n = slices;
    int m = stacks;


    for (int i = 0; i < (m+1); i++) {
        float av = (M_PI/2) - i * (M_PI / m);
        float y = radius * sin(av);
        for (int j = 0; j < n; j++) {
            float ah = j * (2 * M_PI / n);
            float x = radius * sin(ah) * cos(av);
            float z = radius * cos(ah) * cos(av);

            if (y == radius || y == -radius) {
                v[(3 * n * i) + (3 * j)] = 0.0;
                v[(3 * n * i) + (3 * j) + 1] = y;
                v[(3 * n * i) + (3 * j) + 2] = 0.0;
            }
            else {
                v[(3 * n * i) + (3 * j)] = x;
                v[(3 * n * i) + (3 * j) + 1] = y;
                v[(3 * n * i) + (3 * j) + 2] = z;
            }
        }
    }
}
