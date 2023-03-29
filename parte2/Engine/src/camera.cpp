#include "camera.hpp"

Camera::Camera() : position(0.0f, 0.0f, 0.0f),
                   lookAt(0.0f, 0.0f, 0.0f),
                   up(0.0f, 1.0f, 0.0f),
                   fov(60.0f),
                   near(1.0f),
                   far(1000.0f) {}

Camera::Camera(const Point &p, const Point &l, const Point &u, float f, float n, float fa) : position(p),
                                                                                                   lookAt(l),
                                                                                                   up(u),
                                                                                                   fov(f),
                                                                                                   near(n),
                                                                                                   far(fa) {}

Point Camera::getPosition() const
{
    return position;
}

Point Camera::getLookAt() const {
    return lookAt;
}

Point Camera::getUp() const {
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
    position = Point(x, y, z);
}

void Camera::setLookAt(float x, float y, float z) {
    lookAt = Point(x, y, z);
}

void Camera::setUp(float x, float y, float z) {
    up = Point(x, y, z);
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

void Camera::incrementPositionbetaAngle(float angle) {
    position.incrementbeta(angle);
}

void Camera::incrementPositionalphaAngle(float angle) {
    position.incrementalpha(angle);
}

void Camera::incrementPositionRadius(float radius) {
    position.incrementRadius(radius);
}
