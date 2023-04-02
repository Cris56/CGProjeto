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

void Transform::setTranslation(float x, float y, float z) {
    translationAxis = Point(x, y, z);
    transformationOrder.push_back(TRANSLATION);
}

void Transform::setRotation(float x, float y, float z, float time) {
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
