#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Vector3.hpp"
#include <vector>

enum TransformType {
    TRANSLATION,
    ROTATION,
    SCALING
};

class Transform {
public:
    Transform();
    Vector3 getTranslation() const;
    Vector3 getRotation() const;
    float getRotationAngle() const;
    Vector3 getScale() const;
    void setTranslation(float x, float y, float z);
    void setRotation(float x, float y, float z, float angle);
    void setScale(float x, float y, float z);
    std::vector<TransformType> getTransformationOrder() const;
    
private:
    Vector3 translationAxis;
    Vector3 rotationAxis;
    float rotationAngle;
    Vector3 scaleAxis;
    std::vector<TransformType> transformationOrder;
};

#endif // TRANSFORM_HPP
