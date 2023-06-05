#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "point.hpp"
#include "Curva_CATMR_H.hpp"
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

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
    float getTimeForRotation() const;
    Point getScale() const;
    float getTime() const;
    bool getIsAligned() const;
    std::vector<Point> getTranslationPoints() const;
    std::vector<TransformType> getTransformationOrder() const;
    void drawTranslation(const std::vector<Point>& t, float timestp, bool align) const;
    void setTranslation(float x, float y, float z);
    void setRotation(float time, float x, float y, float z);
    void setScale(float x, float y, float z);
    void setTime(float time);
    void setIsAligned(bool isAligned);
    void setNewTranslation();
    void addTranslationPoint(float x, float y, float z);
    
private:
    Point translationAxis;
    Point rotationAxis;
    float timeForRotation;
    Point scaleAxis;
    float time;
    bool isAligned;
    std::vector<TransformType> transformationOrder;
    std::vector<Point> translationPoints;
};

#endif // TRANSFORM_HPP
