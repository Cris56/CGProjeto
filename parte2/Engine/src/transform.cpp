#include "Transform.hpp"

Transform::Transform() : translationAxis(0.0f, 0.0f, 0.0f),
                         rotationAxis(0.0f, 0.0f, 0.0f),
                         rotationAngle(0.0f),
                         scaleAxis(1.0f, 1.0f, 1.0f) {}
                         
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
    translationAxis.x = x;
    translationAxis.y = y;
    translationAxis.z = z;
}

void Transform::setRotation(float x, float y, float z, float angle) {
    rotationAxis.x = x;
    rotationAxis.y = y;
    rotationAxis.z = z;
    rotationAngle = angle;
}

void Transform::setScale(float x, float y, float z) {
    scaleAxis.x = x;
    scaleAxis.y = y;
    scaleAxis.z = z;
}