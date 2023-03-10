#include "plane.hpp"
#include "geometry.hpp"

vector<Point> vplan;


void genPlane(float size, int divisions, float* v) {
    int n = divisions;
    const int numv = (n + 1) * (n + 1);
    vplan.resize(numv);
    verticesPlano(size, divisions);
    int j = 0;
    //organizar por triangulos os pontos
    for (int i = 0; i < numv - (n + 1); i++) {
        if ((i) % n != 0 || i == 0) {

            v[j] = vplan[i].x;
            v[j + 1] = vplan[i].y;
            v[j + 2] = vplan[i].z;
            j += 3;
            v[j] = vplan[i + n + 1].x;
            v[j + 1] = vplan[i + n + 1].y;
            v[j + 2] = vplan[i + n + 1].z;
            j += 3;
            v[j] = vplan[i + 1].x;
            v[j + 1] = vplan[i + 1].y;
            v[j + 2] = vplan[i + 1].z;
            j += 3;

            v[j] = vplan[i].x;
            v[j + 1] = vplan[i].y;
            v[j + 2] = vplan[i].z;
            j += 3;
            v[j] = vplan[i + n].x;
            v[j + 1] = vplan[i + n].y;
            v[j + 2] = vplan[i + n].z;
            j += 3;
            v[j] = vplan[i + n + 1].x;
            v[j + 1] = vplan[i + n + 1].y;
            v[j + 2] = vplan[i + n + 1].z;
            j += 3;
        }
    }
}
void verticesPlano(float size, int divisions) {
    float step = size / divisions;
    int index = 0;
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            // Define as coordenadas dos vértices
            float x1 = i * step - size / 2.0f;
            float z1 = j * step - size / 2.0f;
            vplan[index].x = x1;
            vplan[index].y = 0;
            vplan[index].z = z1;
            index++;

        }
    }
}
