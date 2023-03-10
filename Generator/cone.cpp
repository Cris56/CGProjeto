#include "cone.hpp"

void genCone(float coneRadius, float coneHeight, int numSlices, int numStacks, float *v) {

    if (coneRadius <= 0 || coneHeight <= 0 || numSlices < 3 || numStacks < 1) {
        throw std::invalid_argument("Invalid input parameters for genCone function.");
    }

    vector<triangle> coneTrianglesCombined;

    vector<triangle> coneBaseTriangles = genConeBase(coneRadius, numSlices, numStacks);
    vector<triangle> coneBodyTriangles = genConeBody(coneRadius, coneHeight, numSlices, numStacks);

    coneTrianglesCombined.reserve(coneBaseTriangles.size() + coneBodyTriangles.size());
    coneTrianglesCombined.insert(coneTrianglesCombined.end(), coneBaseTriangles.begin(), coneBaseTriangles.end());
    coneTrianglesCombined.insert(coneTrianglesCombined.end(), coneBodyTriangles.begin(), coneBodyTriangles.end());

    int numVCombined = coneTrianglesCombined.size() * 3;

    for (int i = 0, j = 0; j < numVCombined * 3; i++, j += 9) {
        v[j] =     coneTrianglesCombined[i].p1.ponto[0];
        v[j + 1] = coneTrianglesCombined[i].p1.ponto[1];
        v[j + 2] = coneTrianglesCombined[i].p1.ponto[2];

        v[j + 3] = coneTrianglesCombined[i].p2.ponto[0];
        v[j + 4] = coneTrianglesCombined[i].p2.ponto[1];
        v[j + 5] = coneTrianglesCombined[i].p2.ponto[2];

        v[j + 6] = coneTrianglesCombined[i].p3.ponto[0];
        v[j + 7] = coneTrianglesCombined[i].p3.ponto[1];
        v[j + 8] = coneTrianglesCombined[i].p3.ponto[2];
    }
    return;
}

vector<triangle> genConeBase(float coneRadius, int numSlices, int numStacks) {

    // angleBetweenSlices representa o ângulo entre slices
    float angleBetweenSlices = 2 * M_PI / (float)numSlices;

    vector<triangle> triangles;

    for (int i = 0; i <= numSlices; i++) {
        float deltaAngle = i * angleBetweenSlices;

        ponto point1;
        point1.ponto[0] = 0.0f;
        point1.ponto[1] = 0.0f;
        point1.ponto[2] = 0.0f;

        ponto point2;
        point2.ponto[0] = sin(deltaAngle) * coneRadius;
        point2.ponto[1] = 0.0f;
        point2.ponto[2] = cos(deltaAngle) * coneRadius;

        ponto point3;
        point3.ponto[0] = sin(deltaAngle + angleBetweenSlices) * coneRadius;
        point3.ponto[1] = 0.0f;
        point3.ponto[2] = cos(deltaAngle + angleBetweenSlices) * coneRadius;

        triangle triangle;
        triangle.p1 = point3;
        triangle.p2 = point2;
        triangle.p3 = point1;
        triangles.push_back(triangle);
    }

    return triangles;
}

vector<triangle> genConeBody(float radius, float height, int slices, int stacks) {

    vector<triangle> triangles;

    // alpha representa o ângulo entre slices
    float angleBetweenSlices = 2 * M_PI / (float)slices;

    // stackHeight representa a altura de cada stack
    float stackHeight = height / (float)stacks;

    float topRadius, bottomRadius, topHeight, bottomHeight;

    for (int j = 0; j < stacks; j++) {
    
        bottomHeight = j * stackHeight;
        bottomRadius = radius - ((radius / (float)stacks) * j);

        topHeight = (j + 1) * stackHeight;
        topRadius = radius - ((radius / (float)stacks) * (j + 1));

        for (int i = 0; i < slices; i++) {

            float deltaAngle = i * angleBetweenSlices;

            ponto point1;
            point1.ponto[0] = bottomRadius * sin(deltaAngle);
            point1.ponto[1] = bottomHeight;
            point1.ponto[2] = bottomRadius * cos(deltaAngle);

            ponto point2;
            point2.ponto[0] = topRadius * sin(deltaAngle + angleBetweenSlices);
            point2.ponto[1] = topHeight;
            point2.ponto[2] = topRadius * cos(deltaAngle + angleBetweenSlices);

            ponto point3;
            point3.ponto[0] = topRadius * sin(deltaAngle);
            point3.ponto[1] = topHeight;
            point3.ponto[2] = topRadius * cos(deltaAngle);

            ponto point4;
            point4.ponto[0] = bottomRadius * sin(deltaAngle + angleBetweenSlices);
            point4.ponto[1] = bottomHeight;
            point4.ponto[2] = bottomRadius * cos(deltaAngle + angleBetweenSlices);

            triangle triangle1;
            triangle1.p1 = point1;
            triangle1.p2 = point2;
            triangle1.p3 = point3;
            triangles.push_back(triangle1);

            triangle triangle2;
            triangle2.p1 = point1;
            triangle2.p2 = point4;
            triangle2.p3 = point2;
            triangles.push_back(triangle2);
        }
    }
    return triangles;
}
