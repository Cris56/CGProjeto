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



void Transform::drawTranslation(const std::vector<Point>& t, float timestp, bool align) const{
    const float elapsed_time = glutGet(GLUT_ELAPSED_TIME);
    const float current_time = fmod(elapsed_time, (timestp * 1000)); 

    unsigned int PONTOS_SIZE = t.size();
    const float TESSELATION = 0.001;

    float curve_length = 0;
    renderCatmullRomCurve(t, PONTOS_SIZE, TESSELATION, &curve_length);

    if (timestp == 0) timestp = 1;

    float speed = curve_length / (time * 1000);
    const float distance = current_time * speed;

    float pos[3] = {0, 0, 0};
    float deriv[3] = {0, 0, 0};

    getGlobalCatmullRomPoint(distance / curve_length, pos, deriv, t, PONTOS_SIZE);
    glTranslatef(pos[0], pos[1], pos[2]);

     if (align == 1) {

        float prev_y[3] = { 0,-1,0 };
        
        float x[3] = { deriv[0], deriv[1], deriv[2] };
        normaliza(x);

        float z[3];
        ProdVet(x, prev_y, z);
        normaliza(z);

        float y[3];
        ProdVet(z, x, y);
        normaliza(y);

        memcpy(prev_y, y, 3 * sizeof(float));
        float m[16];
        buildRotMatrix(x, y, z, m);
        glMultMatrixf(m);
    }
      
}



void Transform::setTranslation(float x, float y, float z) {
    translationAxis = Point(x, y, z);
    transformationOrder.push_back(TRANSLATION);
}

void Transform::setNewTranslation(){
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
