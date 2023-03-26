#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Vector3.hpp"

class Transform {
public:

    Transform();
    Vector3 getTranslation() const;
    Vector3 getRotation() const;
    Vector3 getScale() const;
    float getRotationAngle() const;
    void setTranslation(float x, float y, float z);
    void setRotation(float x, float y, float z, float angle);
    void setScale(float x, float y, float z);

private:
    Vector3 translationAxis;
    Vector3 rotationAxis;
    float rotationAngle;
    Vector3 scaleAxis;
};

#endif // TRANSFORM_HPP
