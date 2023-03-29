#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "point.hpp"
#include <vector>

enum TransformType {
    TRANSLATION,
    ROTATION,
    SCALING
};

class Transform {
public:
    Transform();
    Point getTranslation() const;
    Point getRotation() const;
    float getRotationAngle() const;
    Point getScale() const;
    void setTranslation(float x, float y, float z);
    void setRotation(float x, float y, float z, float angle);
    void setScale(float x, float y, float z);
    std::vector<TransformType> getTransformationOrder() const;
    
private:
    Point translationAxis;
    Point rotationAxis;
    float rotationAngle;
    Point scaleAxis;
    std::vector<TransformType> transformationOrder;
};

#endif // TRANSFORM_HPP
