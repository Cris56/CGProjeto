#include "Transform.hpp"

Transform::Transform() : translationAxis(0.0f, 0.0f, 0.0f),
                         rotationAxis(0.0f, 0.0f, 0.0f),
                         rotationAngle(0.0f),
                         scaleAxis(1.0f, 1.0f, 1.0f) {
    transformationOrder.reserve(3);
}

Vector3 Transform::getTranslation() const {
    return translationAxis;
}

Vector3 Transform::getRotation() const {
    return rotationAxis;
}

float Transform::getRotationAngle() const {
    return rotationAngle;
}

Vector3 Transform::getScale() const {
    return scaleAxis;
}

void Transform::setTranslation(float x, float y, float z) {
    translationAxis.setX(x);
    translationAxis.setY(y);
    translationAxis.setZ(z);
    transformationOrder.push_back(TRANSLATION);
}

void Transform::setRotation(float x, float y, float z, float angle) {
    rotationAxis.setX(x);
    rotationAxis.setY(y);
    rotationAxis.setZ(z);
    rotationAngle = angle;
    transformationOrder.push_back(ROTATION);
}

void Transform::setScale(float x, float y, float z) {
    scaleAxis.setX(x);
    scaleAxis.setY(y);
    scaleAxis.setZ(z);
    transformationOrder.push_back(SCALING);
}

std::vector<TransformType> Transform::getTransformationOrder() const {
    return transformationOrder;
}
