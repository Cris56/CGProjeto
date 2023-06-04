#include "transform.hpp"

Transform::Transform() : translationAxis(0.0f, 0.0f, 0.0f),
                         rotationAxis(0.0f, 0.0f, 0.0f),
                         timeForRotation(0.0f),
                         scaleAxis(1.0f, 1.0f, 1.0f), 
                         time (0.0f),
                         isAligned(false) {
    transformationOrder.reserve(3);
}

Point Transform::getTranslation() const {
    return translationAxis;
}

Point Transform::getRotation() const {
    return rotationAxis;
}

float Transform::getTimeForRotation() const {
    return timeForRotation;
}

Point Transform::getScale() const {
    return scaleAxis;
}

float Transform::getTime() const {
    return time;
}

bool Transform::getIsAligned() const {
    return isAligned;
}

std::vector<Point> Transform::getTranslationPoints() const {
    return translationPoints;
}

void Transform::getCurvePoint(std::vector<Point> c, float tt, float* pos, float* deriv) const {
    int conta = c.size();
    if (conta == 0) {
        // Lidar com o vetor vazio, atribuindo valores padrão a pos e deriv
        std::vector<Point> defaultVector(4, Point(0.0f, 0.0f, 0.0f));
        c = defaultVector;
        pos[0] = 0.0f;
        pos[1] = 0.0f;
        pos[2] = 0.0f;
        deriv[0] = 0.0f;
        deriv[1] = 0.0f;
        deriv[2] = 0.0f;
        return;
    } //para evitar floating point exception

    float t = tt * conta;
    int index = static_cast<int>(floor(t));
    t = t - index;

    int indices[4];
    indices[0] = (index + conta - 1) % conta;
    indices[1] = (indices[0] + 1) % conta;
    indices[2] = (indices[1] + 1) % conta;
    indices[3] = (indices[2] + 1) % conta;

    float p[4][3];
    for (int i = 0; i < 4; i++) {
        p[i][0] = c.at(indices[i]).getX();
        p[i][1] = c.at(indices[i]).getY();
        p[i][2] = c.at(indices[i]).getZ();
    }
    CMRPoint(t, p[0], p[1], p[2], p[3], pos, deriv);
}


void Transform::drawTranslation(const std::vector<Point>& t, float timestp) const{
    float pos[3] = {0,0,0};
    float deriv[3] = {0,0,0};
    if (timestp == 0) timestp = 1; //para evitar floating point exception
    float scaledT = glutGet(GLUT_ELAPSED_TIME)/timestp;
    //printf("\n%f\n", scaledT);

    getCurvePoint(t, scaledT, pos, deriv);
    
    glLoadIdentity(); // Reinicia a matriz de transformação
    glTranslatef(pos[0], pos[1], pos[2]);
    
    normaliza(deriv);

    Point p(0, 1, 0);
    float z[3];
    ProdVet(deriv, reinterpret_cast<float*>(&p), z);
    normaliza(z);

    ProdVet(z, deriv, reinterpret_cast<float*>(&p));
    normaliza(reinterpret_cast<float*>(&p));

    float rotateMatrix[4][4];
    makeMatrix(deriv, reinterpret_cast<float*>(&p), z, reinterpret_cast<float*>(rotateMatrix));

    glMultMatrixf(reinterpret_cast<float*>(rotateMatrix));
}


void Transform::setTranslation(float x, float y, float z) {
    translationAxis = Point(x, y, z);
    transformationOrder.push_back(TRANSLATION);
}

void Transform::setRotation(float time, float x, float y, float z) {
    rotationAxis = Point(x, y, z);
    timeForRotation = time;
    transformationOrder.push_back(ROTATION);
}

void Transform::setScale(float x, float y, float z) {
    scaleAxis = Point(x, y, z);
    transformationOrder.push_back(SCALING);
}

void Transform::setTime(float time) {
    this->time = time;
}

void Transform::setIsAligned(bool isAligned) {
    this->isAligned = isAligned;
}

void Transform::addTranslationPoint(float x, float y, float z) {
    Point translationPoint(x, y, z);
    translationPoints.push_back(translationPoint);
}

std::vector<TransformType> Transform::getTransformationOrder() const {
    return transformationOrder;
}
