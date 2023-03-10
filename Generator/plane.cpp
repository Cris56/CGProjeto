#include "plane.hpp"

struct ponto { float ponto[3]; };
vector<ponto> vplan;


void genPlane(float size, int divisions, float* v) {
    int n = divisions;
    const int numv = (n + 1) * (n + 1);
    vplan.resize(numv);
    verticesPlano(size, divisions);
    int j = 0;
    //organizar por triangulos os pontos
    for (int i = 0; i < numv - (n + 1); i++) {
        if ((i + 1) % (n + 1) != 0 && (i % (n + 1) != 0)) { // vs intermédios fazem 2 triângulos
            v[j] = vplan[i].ponto[0];
            v[j + 1] = vplan[i].ponto[1];
            v[j + 2] = vplan[i].ponto[2];
            j += 3;
            v[j] = vplan[i + 1].ponto[0];
            v[j + 1] = vplan[i + 1].ponto[1];
            v[j + 2] = vplan[i + 1].ponto[2];
            j += 3;
            v[j] = vplan[i + n + 1].ponto[0];
            v[j + 1] = vplan[i + n + 1].ponto[1];
            v[j + 2] = vplan[i + n + 1].ponto[2];
            j += 3;

            v[j] = vplan[i].ponto[0];
            v[j + 1] = vplan[i].ponto[1];
            v[j + 2] = vplan[i].ponto[2];
            j += 3;
            v[j] = vplan[i + n + 1].ponto[0];
            v[j + 1] = vplan[i + n + 1].ponto[1];
            v[j + 2] = vplan[i + n + 1].ponto[2];
            j += 3;
            v[j] = vplan[i + n].ponto[0];
            v[j + 1] = vplan[i + n].ponto[1];
            v[j + 2] = vplan[i + n].ponto[2];
            j += 3;
        }
        else if (i % (n + 1) == 0 && (i + n + 1 < numv)) { // vértices de "trás" fazem só 1
            v[j] = vplan[i].ponto[0];
            v[j + 1] = vplan[i].ponto[1];
            v[j + 2] = vplan[i].ponto[2];
            j += 3;
            v[j] = vplan[i + 1].ponto[0];
            v[j + 1] = vplan[i + 1].ponto[1];
            v[j + 2] = vplan[i + 1].ponto[2];
            j += 3;
            v[j] = vplan[i + n + 1].ponto[0];
            v[j + 1] = vplan[i + n + 1].ponto[1];
            v[j + 2] = vplan[i + n + 1].ponto[2];
            j += 3;
        }
        else if ((i + 1) % (n + 1) == 0 && (i + n + 1 < numv)) { // vertices da "frente" fazem o que está atrás dele
            v[j] = vplan[i].ponto[0];
            v[j + 1] = vplan[i].ponto[1];
            v[j + 2] = vplan[i].ponto[2];
            j += 3;
            v[j] = vplan[i + n + 1].ponto[0];
            v[j + 1] = vplan[i + n + 1].ponto[1];
            v[j + 2] = vplan[i + n + 1].ponto[2];
            j += 3;
            v[j] = vplan[i + n].ponto[0];
            v[j + 1] = vplan[i + n].ponto[1];
            v[j + 2] = vplan[i + n].ponto[2];
            j += 3;
        }
    }
}

void verticesPlano(float size, int divisions) {
    float step = size / divisions;
    int index = 0;
    for (int i = 0; i < divisions + 1; i++) {
        float x1 = i * step - size / 2.0f;
        for (int j = 0; j < divisions + 1; j++) {
            // Define as coordenadas dos vértices
            float z1 = j * step - size / 2.0f;
            vplan[index].ponto[0] = x1;
            vplan[index].ponto[1] = 0;
            vplan[index].ponto[2] = z1;
            index++;

        }
    }
}
