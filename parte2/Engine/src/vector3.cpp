#include "Vector3.hpp"

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::getX() const {
    return x;
}

float Vector3::getY() const {
    return y;
}

float Vector3::getZ() const {
    return z;
}

void Vector3::setVector3(float x, float y, float z) {
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}


void Vector3::setX(float x) {
    this->x = x;
}

void Vector3::setY(float y) {
    this->y = y;
}

void Vector3::setZ(float z) {
    this->z = z;
}
