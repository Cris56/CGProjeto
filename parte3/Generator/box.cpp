
#include "box.hpp"

vector<Point> vBox;

void genBox(float length, int div, float* v) {
    
    int n = div;
    const int numv = (div + 1) * (div + 1) * 6;
    vBox.resize(numv);
    verticesBox(length, div);

    // organizar por triângulos para pôr no v
    int j = 0;
    int i = 0;
    int numvface = numv / 6;

    // frente
    for (i = 0; i < numvface - (n + 1); i++) {
        if (((i+1) % (n+1) != 0) && (i%(n+1) != 0)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n].x;
            v[j + 1] = vBox[i + n].y;
            v[j + 2] = vBox[i + n].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;

            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i + 1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;
        }
        else if ((i%(n+1)) == 0 && (i+n+1<numvface)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i + 1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;
        }
        else if (((i + 1) % (n + 1) == 0) && (i+n+1<=numvface)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n].x;
            v[j + 1] = vBox[i + n].y;
            v[j + 2] = vBox[i + n].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
        }
    }

    // tras
    for (i = numvface-1; i < 2*numvface - (n + 1); i++) {
        if ((i + 1) % (n + 1) != 0) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i + 1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;
            v[j] = vBox[i + n + 2].x;
            v[j + 1] = vBox[i + n + 2].y;
            v[j + 2] = vBox[i + n + 2].z;
            j += 3;
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 2].x;
            v[j + 1] = vBox[i + n + 2].y;
            v[j + 2] = vBox[i + n + 2].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
        }
    }

    // esquerda
    for (i = 2*numvface-1; i < 3 * numvface - (n + 1); i++) {
        if ((i + 1) % (n + 1) != 0) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
            v[j] = vBox[i + n + 2].x;
            v[j + 1] = vBox[i + n + 2].y;
            v[j + 2] = vBox[i + n + 2].z;
            j += 3;
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 2].x;
            v[j + 1] = vBox[i + n + 2].y;
            v[j + 2] = vBox[i + n + 2].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i + 1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;
        }
    }
    
    //direita
    for (i = 3*numvface-1; i < 4 * numvface - (n+1); i++) {
        if (((i + 1) % (n + 1) != 0) && (i % (n + 1) != 0)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i + 1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;

            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
            v[j] = vBox[i + n].x;
            v[j + 1] = vBox[i + n].y;
            v[j + 2] = vBox[i + n].z;
            j += 3;
        }
        else if ((i % (n + 1) == 0) && (i + n + 1 < 4 * numvface)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i + 1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
        }
        else if (((i + 1) % (n + 1) == 0) && (i + n + 1 <= 4 * numvface)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
            v[j] = vBox[i + n].x;
            v[j + 1] = vBox[i + n].y;
            v[j + 2] = vBox[i + n].z;
            j += 3;
        }
    }

    //baixo
    for (i = 4 * numvface-1; i < 5 * numvface - (n + 1); i++) {
        if ((i + 1) % (n + 1) != 0) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 2].x;
            v[j + 1] = vBox[i + n + 2].y;
            v[j + 2] = vBox[i + n + 2].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;

            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i + 1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;
            v[j] = vBox[i + n + 2].x;
            v[j + 1] = vBox[i + n + 2].y;
            v[j + 2] = vBox[i + n + 2].z;
            j += 3;
        }
    }

    //cima 
    for (i = 5 * numvface-1; i < 6 * numvface - (n + 1); i++) {
        if (((i+1) % (n+1) != 0) && (i%(n+1) != 0)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i +1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;

            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n].x;
            v[j + 1] = vBox[i + n].y;
            v[j + 2] = vBox[i + n].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
        }
        else if ((i%(n+1) == 0) && (i+n+1<= 6 * numvface)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n+1].x;
            v[j + 1] = vBox[i + n+1].y;
            v[j + 2] = vBox[i + n+1].z;
            j += 3;
            v[j] = vBox[i + 1].x;
            v[j + 1] = vBox[i + 1].y;
            v[j + 2] = vBox[i + 1].z;
            j += 3;
        }
        else if (((i + 1) % (n + 1) == 0) && (i+n+1<=6*numvface)) {
            v[j] = vBox[i].x;
            v[j + 1] = vBox[i].y;
            v[j + 2] = vBox[i].z;
            j += 3;
            v[j] = vBox[i + n].x;
            v[j + 1] = vBox[i + n].y;
            v[j + 2] = vBox[i + n].z;
            j += 3;
            v[j] = vBox[i + n + 1].x;
            v[j + 1] = vBox[i + n + 1].y;
            v[j + 2] = vBox[i + n + 1].z;
            j += 3;
        }
    }

}

// Colocar cada ponto necessário no vBox

// for face trás #1: (div+1) ^ 2, z sempre -1 *
// for face esq #2: 2 * (div+1), x sempre -1 *
// for face dir #3 mesmo mas x sempre 1 
// for face baixo #4 div+1, y sempre -1
// for face cima #5 div+1, y sempre 1
// for face frente #6 (div+1)^2, z sempre 1


void verticesBox(float length, int div) {
    float size = length / div;
    float startX = -length / 2.0;
    float startY = -length / 2.0;
    float startZ = -length / 2.0;
    int index = 0;

    //face da frente
    for (int i = 0; i < (div + 1); ++i) {
        float x = startX + (i * size);
        for (int j = 0; j < (div + 1); ++j) {
            float y = startY + (j * size);
            vBox[index].x = x;
            vBox[index].y = y;
            vBox[index].z = -startZ;
            index++;
        }
    }

    //face de tras
    for (int i = 0; i < (div + 1); ++i) {
        float x = startX + (i * size);
        for (int j = 0; j < (div + 1); ++j) {
            float y = startY + (j * size);
            vBox[index].x = x;
            vBox[index].y = y;
            vBox[index].z = startZ;
            index++;
        }
    }

    //face da esquerda
    for (int i = 0; i < div+1; ++i) {
        float z = startZ + (i * size);
        for (int j = 0; j < div + 1; ++j) {
            float y = startY + (j * size);
            vBox[index].x = startX;
            vBox[index].y = y;
            vBox[index].z = z;
            index++;
        }
    }

    //face da direita
    for (int i = 0; i < div+1; ++i) {
        float z = startZ + (i * size);
        for (int j = 0; j < div + 1; ++j) {
            float y = startY + (j * size);
            vBox[index].x = -startX;
            vBox[index].y = y;
            vBox[index].z = z;
            index++;
        }
    }

    //face de baixo
    for (int i = 0; i < div+1; ++i) {
        float z = startZ + (i * size);
        for (int j = 0; j < div+1; ++j) {
            float x = startX + (j * size);
            vBox[index].x = x;
            vBox[index].y = startY;
            vBox[index].z = z;
            index++;
        }
    }

    //face de cima
    for (int i = 0; i < div+1; ++i) {
        float z = startZ + (i * size);
        for (int j = 0; j < div+1; ++j) {
            float x = startX + (j * size);
            vBox[index].x = x;
            vBox[index].y = -startY;
            vBox[index].z = z;
            index++;
        }
    }
}