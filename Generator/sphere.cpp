#include "sphere.hpp"
vector<ponto> vSphere;

void genSphere(float radius, int slices, int stacks, float *v) {
    int n = slices;
    int m = stacks;

    const int numv = n * (m + 1);
    vSphere.resize(numv);
    verticesSphere(radius, n, m);

    int j = 0;
    for (int i = 0; i < numv-n; i++) {
        int ex = 0;
        if ((i + 1) % n == 0 && i > 0) {
            ex = m;
        }
        v[j] = vSphere[i].ponto[0];
        v[j + 1] = vSphere[i].ponto[1];
        v[j + 2] = vSphere[i].ponto[2];
        j += 3;
        v[j] = vSphere[i - ex + n + 1].ponto[0];
        v[j + 1] = vSphere[i - ex + n + 1].ponto[1];
        v[j + 2] = vSphere[i - ex + n + 1].ponto[2];
        j += 3;
        v[j] = vSphere[i - ex + 1].ponto[0];
        v[j + 1] = vSphere[i - ex + 1].ponto[1];
        v[j + 2] = vSphere[i - ex + 1].ponto[2];
        j += 3;
        v[j] = vSphere[i].ponto[0];
        v[j + 1] = vSphere[i].ponto[1];
        v[j + 2] = vSphere[i].ponto[2];
        j += 3;
        v[j] = vSphere[i + n].ponto[0];
        v[j + 1] = vSphere[i + n].ponto[1];
        v[j + 2] = vSphere[i + n].ponto[2];
        j += 3;
        v[j] = vSphere[i - ex + n + 1].ponto[0];
        v[j + 1] = vSphere[i - ex + n + 1].ponto[1];
        v[j + 2] = vSphere[i - ex + n + 1].ponto[2];
        j += 3;
    }
}

void verticesSphere(float radius, int slices, int stacks) {
    int n = slices;
    int m = stacks;
    const int numv = n * (m + 1);
    int a = 0;
    for (int i = 0; i < (m + 1); i++) {
        float av = (M_PI / 2) - i * (M_PI / m);
        float y = radius * sin(av);
        for (int j = 0; j < n; j++) {
            float ah = j * (2 * M_PI / n);
            float x = radius * sin(ah) * cos(av);
            float z = radius * cos(ah) * cos(av);

            if (y == radius || y == -radius) {
                vSphere[a].ponto[0] = 0.0;
                vSphere[a].ponto[1] = y;
                vSphere[a].ponto[2] = 0.0;
            }
            else {
                vSphere[a].ponto[0] = x;
                vSphere[a].ponto[1] = y;
                vSphere[a].ponto[2] = z;
            }
            a++;
        }
    }
}
