#include "sphere.hpp"

vector<Point> vSphere;
vector<Point> vSphereTex;

void genSphere(float radius, int slices, int stacks, float* v, float* vt) {

    const int numv = slices * (stacks + 1);
    vSphere.resize(numv);
    verticesSphere(radius, slices, stacks);

    vSphereTex.resize(numv);
    genTexSphere(slices, stacks, vSphereTex.data());

    int j = 0;
    for (int i = 0; i < numv - slices; i++) {
        int ex = 0;
        if ((i + 1) % slices == 0 && i > 0) {
            ex = stacks;
        }

        v[j] = vSphere[i].x;                         vt[j] = vSphereTex[i].x;
        v[j + 1] = vSphere[i].y;                     vt[j + 1] = vSphereTex[i].y;
        v[j + 2] = vSphere[i].z;                     vt[j + 2] = vSphereTex[i].z;
        j += 3;

        v[j] = vSphere[i - ex + slices + 1].x;       vt[j] = vSphereTex[i - ex + slices + 1].x;
        v[j + 1] = vSphere[i - ex + slices + 1].y;   vt[j + 1] = vSphereTex[i - ex + slices + 1].y;
        v[j + 2] = vSphere[i - ex + slices + 1].z;   vt[j + 2] = vSphereTex[i - ex + slices + 1].z;
        if (ex == stacks) vt[j] = 1;
        j += 3;

        v[j] = vSphere[i - ex + 1].x;                vt[j] = vSphereTex[i - ex + 1].x;
        v[j + 1] = vSphere[i - ex + 1].y;            vt[j + 1] = vSphereTex[i - ex + 1].y;
        v[j + 2] = vSphere[i - ex + 1].z;            vt[j + 2] = vSphereTex[i - ex + 1].z;
        if (ex == stacks) vt[j] = 1;
        j += 3;

        v[j] = vSphere[i].x;                         vt[j] = vSphereTex[i].x;
        v[j + 1] = vSphere[i].y;                     vt[j + 1] = vSphereTex[i].y;
        v[j + 2] = vSphere[i].z;                     vt[j + 2] = vSphereTex[i].z;
        j += 3;

        v[j] = vSphere[i + slices].x;                vt[j] = vSphereTex[i + slices].x;
        v[j + 1] = vSphere[i + slices].y;            vt[j + 1] = vSphereTex[i + slices].y;
        v[j + 2] = vSphere[i + slices].z;            vt[j + 2] = vSphereTex[i + slices].z;
        j += 3;

        v[j] = vSphere[i - ex + slices + 1].x;       vt[j] = vSphereTex[i - ex + slices + 1].x;
        v[j + 1] = vSphere[i - ex + slices + 1].y;   vt[j + 1] = vSphereTex[i - ex + slices + 1].y;
        v[j + 2] = vSphere[i - ex + slices + 1].z;   vt[j + 2] = vSphereTex[i - ex + slices + 1].z;
        if (ex == stacks) vt[j] = 1;
        j += 3;
    }
}

void verticesSphere(float radius, int slices, int stacks) {
    const int numv = slices * (stacks + 1);
    int a = 0;
    for (int i = 0; i < (stacks + 1); i++) {
        float av = (M_PI / 2) - i * (M_PI / stacks);
        float y = radius * sin(av);
        for (int j = 0; j < slices; j++) {
            float ah = j * (2 * M_PI / slices);
            float x = radius * sin(ah) * cos(av);
            float z = radius * cos(ah) * cos(av);

            if (y == radius || y == -radius) {
                vSphere[a].x = 0.0;
                vSphere[a].y = y;
                vSphere[a].z = 0.0;
            }
            else {
                vSphere[a].x = x;
                vSphere[a].y = y;
                vSphere[a].z = z;
            }
            a++;
        }
    }
}
