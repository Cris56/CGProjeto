#include "cone.hpp"

void genCone(float coneRadius, float coneHeight, int numSlices, int numStacks, float *v) {

    if (coneRadius <= 0 || coneHeight <= 0 || numSlices < 3 || numStacks < 1) {
        throw std::invalid_argument("Invalid input parameters for genCone function.");
    }

    vector<Triangle> coneTrianglesCombined;

    vector<Triangle> coneBaseTriangles = genConeBase(coneRadius, numSlices, numStacks);
    vector<Triangle> coneBodyTriangles = genConeBody(coneRadius, coneHeight, numSlices, numStacks);

    coneTrianglesCombined.reserve(coneBaseTriangles.size() + coneBodyTriangles.size());
    coneTrianglesCombined.insert(coneTrianglesCombined.end(), coneBaseTriangles.begin(), coneBaseTriangles.end());
    coneTrianglesCombined.insert(coneTrianglesCombined.end(), coneBodyTriangles.begin(), coneBodyTriangles.end());

    int numVCombined = coneTrianglesCombined.size() * 3;

    for (int i = 0, j = 0; j < numVCombined * 3; i++, j += 9) {
        v[j] =     coneTrianglesCombined[i].vertex1.x;
        v[j + 1] = coneTrianglesCombined[i].vertex1.y;
        v[j + 2] = coneTrianglesCombined[i].vertex1.z;

        v[j + 3] = coneTrianglesCombined[i].vertex2.x;
        v[j + 4] = coneTrianglesCombined[i].vertex2.y;
        v[j + 5] = coneTrianglesCombined[i].vertex2.z;

        v[j + 6] = coneTrianglesCombined[i].vertex3.x;
        v[j + 7] = coneTrianglesCombined[i].vertex3.y;
        v[j + 8] = coneTrianglesCombined[i].vertex3.z;
    }
    return;
}

vector<Triangle> genConeBase(float coneRadius, int numSlices, int numStacks) {

    // angleBetweenSlices representa o ângulo entre slices
    float angleBetweenSlices = 2 * M_PI / (float)numSlices;

    vector<Triangle> triangles;

    for (int i = 0; i <= numSlices; i++) {
        float deltaAngle = i * angleBetweenSlices;

        Point point1;
        point1.x = 0.0f;
        point1.y = 0.0f;
        point1.z = 0.0f;

        Point point2;
        point2.x = sin(deltaAngle) * coneRadius;
        point2.y = 0.0f;
        point2.z = cos(deltaAngle) * coneRadius;

        Point point3;
        point3.x = sin(deltaAngle + angleBetweenSlices) * coneRadius;
        point3.y = 0.0f;
        point3.z = cos(deltaAngle + angleBetweenSlices) * coneRadius;

        Triangle triangle;
        triangle.vertex1 = point3;
        triangle.vertex2 = point2;
        triangle.vertex3 = point1;
        triangles.push_back(triangle);
    }

    return triangles;
}

vector<Triangle> genConeBody(float radius, float height, int slices, int stacks) {

    vector<Triangle> triangles;

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

            Point point1;
            point1.x = bottomRadius * sin(deltaAngle);
            point1.y = bottomHeight;
            point1.z = bottomRadius * cos(deltaAngle);

            Point point2;
            point2.x = topRadius * sin(deltaAngle + angleBetweenSlices);
            point2.y = topHeight;
            point2.z = topRadius * cos(deltaAngle + angleBetweenSlices);

            Point point3;
            point3.x = topRadius * sin(deltaAngle);
            point3.y = topHeight;
            point3.z = topRadius * cos(deltaAngle);

            Point point4;
            point4.x = bottomRadius * sin(deltaAngle + angleBetweenSlices);
            point4.y = bottomHeight;
            point4.z = bottomRadius * cos(deltaAngle + angleBetweenSlices);

            Triangle triangle1;
            triangle1.vertex1 = point1;
            triangle1.vertex2 = point2;
            triangle1.vertex3 = point3;
            triangles.push_back(triangle1);

            Triangle triangle2;
            triangle2.vertex1 = point1;
            triangle2.vertex2 = point4;
            triangle2.vertex3 = point2;
            triangles.push_back(triangle2);
        }
    }
    return triangles;
}
