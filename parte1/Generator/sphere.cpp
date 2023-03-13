#include "sphere.hpp"

vector<Point> vSphere;

void genSphere(float radius, int numSlices, int numStacks, float* v) {

    const int numv = numSlices * (numStacks + 1);
    vSphere.resize(numv);
    verticesSphere(radius, numSlices, numStacks);

    int j = 0;
    for (int i = 0; i < numv - numSlices; i++) {
        int ex = 0;
        if ((i + 1) % numSlices == 0 && i > 0) {
            ex = numStacks;
        }

        v[j]     = vSphere[i].x;
        v[j + 1] = vSphere[i].y;
        v[j + 2] = vSphere[i].z;
        j += 3;

        v[j]     = vSphere[i - ex + numSlices + 1].x;
        v[j + 1] = vSphere[i - ex + numSlices + 1].y;
        v[j + 2] = vSphere[i - ex + numSlices + 1].z;
        j += 3;

        v[j]     = vSphere[i - ex + 1].x;
        v[j + 1] = vSphere[i - ex + 1].y;
        v[j + 2] = vSphere[i - ex + 1].z;
        j += 3;

        v[j]     = vSphere[i].x;
        v[j + 1] = vSphere[i].y;
        v[j + 2] = vSphere[i].z;
        j += 3;

        v[j]     = vSphere[i + numSlices].x;
        v[j + 1] = vSphere[i + numSlices].y;
        v[j + 2] = vSphere[i + numSlices].z;
        j += 3;

        v[j]     = vSphere[i - ex + numSlices + 1].x;
        v[j + 1] = vSphere[i - ex + numSlices + 1].y;
        v[j + 2] = vSphere[i - ex + numSlices + 1].z;
        j += 3;
    }
}

void verticesSphere(float radius, int numSlices, int numStacks) {
    const int numv = numSlices * (numStacks + 1);
    int a = 0;
    for (int i = 0; i < (numStacks + 1); i++) {
        float av = (M_PI / 2) - i * (M_PI / numStacks);
        float y = radius * sin(av);
        for (int j = 0; j < numSlices; j++) {
            float ah = j * (2 * M_PI / numSlices);
            float x = radius * sin(ah) * cos(av);
            float z = radius * cos(ah) * cos(av);

            Point p = { x, y, z };
            vSphere[a] = p;

            a++;
        }
    }
}
