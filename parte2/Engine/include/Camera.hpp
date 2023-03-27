#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vector3.hpp"

class Camera {
public:

    Camera();
    Camera(const Vector3 &p, const Vector3 &l, const Vector3 &u, float f, float n, float fa);
    Vector3 getPosition() const;
    Vector3 getLookAt() const;
    Vector3 getUp() const;
    float getFov() const;
    float getNear() const;
    float getFar() const;
    void setPosition(float x, float y, float z);
    void setLookAt(float x, float y, float z);
    void setUp(float x, float y, float z);
    void setFov(float f);
    void setNear(float n);
    void setFar(float f);

private:
    Vector3 position;
    Vector3 lookAt;
    Vector3 up;

    float fov;
    float near;
    float far;
};

#endif // CAMERA_HPP