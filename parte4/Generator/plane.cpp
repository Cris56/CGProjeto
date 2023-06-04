#include "plane.hpp"

vector<Point> vPlane;
vector<Point> vPlaneTex;

void genPlane(float size, int divisions, float* v, float* vt) {
    int n = divisions;
    const int numv = (n + 1) * (n + 1);
    vPlane.resize(numv);
    verticesPlano(size, divisions);

    vPlaneTex.resize(numv);
    genTexPlane(vPlane.data(), divisions, size, vPlaneTex.data());

    int j = 0;
    
    for (int i = 0; i < numv - (n + 1); i++) {
        if ((i + 1) % (n + 1) != 0 && (i % (n + 1) != 0)) { 
            v[j] = vPlane[i].x;             vt[j] = vPlaneTex[i].x;
            v[j + 1] = vPlane[i].y;         vt[j + 1] = vPlaneTex[i].y;
            v[j + 2] = vPlane[i].z;         vt[j + 2] = vPlaneTex[i].z;
            j += 3;
            v[j] = vPlane[i + 1].x;         vt[j] = vPlaneTex[i + 1].x;
            v[j + 1] = vPlane[i + 1].y;     vt[j + 1] = vPlaneTex[i + 1].y;
            v[j + 2] = vPlane[i + 1].z;     vt[j + 2] = vPlaneTex[i + 1].z;
            j += 3;
            v[j] = vPlane[i + n + 1].x;     vt[j] = vPlaneTex[i + n + 1].x;
            v[j + 1] = vPlane[i + n + 1].y; vt[j + 1] = vPlaneTex[i + n + 1].y;
            v[j + 2] = vPlane[i + n + 1].z; vt[j + 2] = vPlaneTex[i + n + 1].z;
            j += 3;

            v[j] = vPlane[i].x;             vt[j] = vPlaneTex[i].x;
            v[j + 1] = vPlane[i].y;         vt[j + 1] = vPlaneTex[i].y;
            v[j + 2] = vPlane[i].z;         vt[j + 2] = vPlaneTex[i].z;
            j += 3;
            v[j] = vPlane[i + n + 1].x;     vt[j] = vPlaneTex[i + n + 1].x;
            v[j + 1] = vPlane[i + n + 1].y; vt[j + 1] = vPlaneTex[i + n + 1].y;
            v[j + 2] = vPlane[i + n + 1].z; vt[j + 2] = vPlaneTex[i + n + 1].z;
            j += 3;
            v[j] = vPlane[i + n].x;         vt[j] = vPlaneTex[i + n].x;
            v[j + 1] = vPlane[i + n].y;     vt[j + 1] = vPlaneTex[i + n].y;
            v[j + 2] = vPlane[i + n].z;     vt[j + 2] = vPlaneTex[i + n].z;
            j += 3;
        }
        else if (i % (n + 1) == 0 && (i + n + 1 < numv)) { 
            v[j] = vPlane[i].x;             vt[j] = vPlaneTex[i].x;
            v[j + 1] = vPlane[i].y;         vt[j + 1] = vPlaneTex[i].y;
            v[j + 2] = vPlane[i].z;         vt[j + 2] = vPlaneTex[i].z;
            j += 3;
            v[j] = vPlane[i + 1].x;         vt[j] = vPlaneTex[i + 1].x;
            v[j + 1] = vPlane[i + 1].y;     vt[j + 1] = vPlaneTex[i + 1].y;
            v[j + 2] = vPlane[i + 1].z;     vt[j + 2] = vPlaneTex[i + 1].z;
            j += 3;
            v[j] = vPlane[i + n + 1].x;     vt[j] = vPlaneTex[i + n + 1].x;
            v[j + 1] = vPlane[i + n + 1].y; vt[j + 1] = vPlaneTex[i + n + 1].y;
            v[j + 2] = vPlane[i + n + 1].z; vt[j + 2] = vPlaneTex[i + n + 1].z;
            j += 3;
        }
        else if ((i + 1) % (n + 1) == 0 && (i + n + 1 < numv)) { 
            v[j] = vPlane[i].x;             vt[j] = vPlaneTex[i].x;
            v[j + 1] = vPlane[i].y;         vt[j + 1] = vPlaneTex[i].y;
            v[j + 2] = vPlane[i].z;         vt[j + 2] = vPlaneTex[i].z;
            j += 3;
            v[j] = vPlane[i + n + 1].x;     vt[j] = vPlaneTex[i + n + 1].x;
            v[j + 1] = vPlane[i + n + 1].y; vt[j + 1] = vPlaneTex[i + n + 1].y;
            v[j + 2] = vPlane[i + n + 1].z; vt[j + 2] = vPlaneTex[i + n + 1].z;
            j += 3;
            v[j] = vPlane[i + n].x;         vt[j] = vPlaneTex[i + n].x;
            v[j + 1] = vPlane[i + n].y;     vt[j + 1] = vPlaneTex[i + n].y;
            v[j + 2] = vPlane[i + n].z;     vt[j + 2] = vPlaneTex[i + n].z;
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
            
            float z1 = j * step - size / 2.0f;
            vPlane[index].x = x1;
            vPlane[index].y = 0;
            vPlane[index].z = z1;
            index++;

        }
    }
}

