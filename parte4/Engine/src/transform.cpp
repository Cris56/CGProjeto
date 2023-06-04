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

void Transform::getCurvePoint(const std::vector<Point>& c, float tt, float* pos, float* deriv) const {
    int conta = c.size();
    if (conta < 4) {
        // Não há pontos suficientes para criar uma curva, atribua valores padrão a pos e deriv
        pos[0] = 0.0f;
        pos[1] = 0.0f;
        pos[2] = 0.0f;
        deriv[0] = 0.0f;
        deriv[1] = 0.0f;
        deriv[2] = 0.0f;
        return;
    }

    float scaledT = tt * static_cast<float>(conta - 3); // Ajuste do tamanho da curva

    int index = static_cast<int>(floor(scaledT));
    float tFraction = scaledT - index;

    int indices[4];
    for (int i = 0; i < 4; ++i) {
        indices[i] = (index + i) % conta;
    }

    std::vector<Point> p(4);
    for (int i = 0; i < 4; ++i) {
        p[i] = c[indices[i]];
    }
    CMRPoint(tFraction, p[0], p[1], p[2], p[3], pos, deriv);
}



void Transform::drawTranslation(const std::vector<Point>& t, float timestp) const{
    static float currentTime = 0.0f; // Variável de tempo atualizada a cada quadro

    float pos[3] = {0, 0, 0};
    float deriv[3] = {0, 0, 0};

    if (timestp == 0) timestp = 1; // Para evitar floating point exception

    currentTime += (1.0f / timestp); // Atualiza o tempo a cada quadro

    // Calcula o valor de scaledT com base na variável de tempo atualizada
    float scaledT = currentTime * static_cast<float>(t.size() - 3);

    printf("Tempo: %f\n", scaledT);

    getCurvePoint(t, scaledT, pos, deriv);

    glPushMatrix(); // Salva o estado atual da matriz de modelo-visão

    // Aplica a translação
    glTranslatef(pos[0], pos[1], pos[2]);

    normaliza(deriv);

    Point p(0, 1, 0);
    float z[3];
    ProdVet(deriv, reinterpret_cast<float*>(&p), z);
    normaliza(z);

    ProdVet(z, deriv, reinterpret_cast<float*>(&p));
    normaliza(reinterpret_cast<float*>(&p));

    float xAxis[3] = {deriv[0], deriv[1], deriv[2]};
    float yAxis[3] = {static_cast<float>(p.getX()), static_cast<float>(p.getY()), static_cast<float>(p.getZ())};
    float zAxis[3] = {z[0], z[1], z[2]};

    float rotateMatrix[16];
    makeMatrix(xAxis, yAxis, zAxis, rotateMatrix);

    // Aplica a matriz de rotação
    glMultMatrixf(reinterpret_cast<float*>(rotateMatrix));

    // Desenhe o objeto

    glPopMatrix();

    glutPostRedisplay();
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
