#include "cone.hpp"

void genCone(float radius, float height, int slices, int stacks, float *v) {

    // alpha representa o ângulo entre slices
    float alpha = 2 * M_PI / (float)slices;

    // alturaStack representa a altura de cada stack
    float alturaStack = height / (float)stacks;


    float upper_radius, bottom_radius, upper, bottom;

    vector<triangle> triangles;

    for (int i = 0; i <= slices; i++) {
        float delta_alpha = i * alpha;

        ponto p1;
        p1.ponto[0] = 0.0f;
        p1.ponto[1] = 0.0f;
        p1.ponto[2] = 0.0f;

        ponto p2;
        p2.ponto[0] = sin(delta_alpha) * radius;
        p2.ponto[1] = 0.0f;
        p2.ponto[2] = cos(delta_alpha) * radius;
        
        ponto p3;
        p3.ponto[0] = sin(delta_alpha + alpha) * radius;
        p3.ponto[1] = 0.0f;
        p3.ponto[2] = cos(delta_alpha + alpha) * radius;

        triangle t1;
        t1.p1 = p3;
        t1.p2 = p2;
        t1.p3 = p1;
        triangles.push_back(t1);
    }

    int numv = triangles.size() * 3;

    for (int i = 0, j = 0; j < numv * 3; i++, j+=9) {
        v[j] = triangles[i].p1.ponto[0];
        v[j + 1] = triangles[i].p1.ponto[1];
        v[j + 2] = triangles[i].p1.ponto[2];

        v[j + 3] = triangles[i].p2.ponto[0];
        v[j + 4] = triangles[i].p2.ponto[1];
        v[j + 5] = triangles[i].p2.ponto[2];

        v[j + 6] = triangles[i].p3.ponto[0];
        v[j + 7] = triangles[i].p3.ponto[1];
        v[j + 8] = triangles[i].p3.ponto[2];
    }
    return;
}
