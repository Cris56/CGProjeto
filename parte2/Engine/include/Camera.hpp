#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "point.hpp"

class Camera {
public:

    Camera();
    Camera(const Point &p, const Point &l, const Point &u, float f, float n, float fa);
    Point getPosition() const;
    Point getLookAt() const;
    Point getUp() const;
    float getFov() const;
    float getNear() const;
    float getFar() const;
    void setPosition(float x, float y, float z);
    void setLookAt(float x, float y, float z);
    void setUp(float x, float y, float z);
    void setFov(float f);
    void setNear(float n);
    void setFar(float f);
    void incrementPositionbetaAngle(float angle);
    void incrementPositionalphaAngle(float angle);
    void incrementPositionRadius(float radius);

private:
    Point position;
    Point lookAt;
    Point up;

    float fov;
    float near;
    float far;
};

#endif // CAMERA_HPP