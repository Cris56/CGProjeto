#include "transform.hpp"

Transform::Transform() : translationAxis(0.0f, 0.0f, 0.0f),
                         rotationAxis(0.0f, 0.0f, 0.0f),
                         rotationAngle(0.0f),
                         scaleAxis(1.0f, 1.0f, 1.0f) {
    transformationOrder.reserve(3);
}

Point Transform::getTranslation() const {
    return translationAxis;
}

Point Transform::getRotation() const {
    return rotationAxis;
}

float Transform::getRotationAngle() const {
    return rotationAngle;
}

Point Transform::getScale() const {
    return scaleAxis;
}

void Transform::setTranslation(float x, float y, float z) {
    translationAxis = Point(x, y, z);
    transformationOrder.push_back(TRANSLATION);
}

void Transform::setRotation(float x, float y, float z, float angle) {
    rotationAxis = Point(x, y, z);
    rotationAngle = angle;
    transformationOrder.push_back(ROTATION);
}

void Transform::setScale(float x, float y, float z) {
    scaleAxis = Point(x, y, z);
    transformationOrder.push_back(SCALING);
}

std::vector<TransformType> Transform::getTransformationOrder() const {
    return transformationOrder;
}
