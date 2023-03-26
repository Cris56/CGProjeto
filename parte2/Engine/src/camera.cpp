#include "Camera.hpp"

Camera::Camera() : position(0.0f, 0.0f, 0.0f),
                   lookAt(0.0f, 0.0f, 0.0f),
                   up(0.0f, 1.0f, 0.0f),
                   fov(60.0f),
                   near(1.0f),
                   far(1000.0f) {}

Camera::Camera(const Vector3 &p, const Vector3 &l, const Vector3 &u, float f, float n, float fa) : position(p),
                                                                                                   lookAt(l),
                                                                                                   up(u),
                                                                                                   fov(f),
                                                                                                   near(n),
                                                                                                   far(fa) {}

Vector3 Camera::getPosition() const
{
    return position;
}

Vector3 Camera::getLookAt() const {
    return lookAt;
}

Vector3 Camera::getUp() const {
    return up;
}

float Camera::getFov() const {
    return fov;
}

float Camera::getNear() const {
    return near;
}

float Camera::getFar() const {
    return far;
}

void Camera::setPosition(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
}

void Camera::setLookAt(float x, float y, float z) {
    lookAt.x = x;
    lookAt.y = y;
    lookAt.z = z;
}

void Camera::setUp(float x, float y, float z) {
    up.x = x;
    up.y = y;
    up.z = z;
}

void Camera::setFov(float f) {
    fov = f;
}

void Camera::setNear(float n) {
    near = n;
}

void Camera::setFar(float f) {
    far = f;
}