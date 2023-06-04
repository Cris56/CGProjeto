#ifndef LIGHTS_HPP
#define LIGHTS_HPP

#include "point.hpp"
#include <GL/glew.h>
#include <GL/glut.h>

enum Type {
    POINT,
    DIRECTIONAL,
    SPOTLIGHT
};

class Light {
    private:
        Type type;
        Point pos;
        Point dir;
        int cutoff;

    public:
        Light(Type type, Point pos); // For point and directional lights
        Light(Point pos, Point dir, int cutoff); // For spotlight lights
        Point getPosition();
        Point getDirection();
        int getCutoff();
        void render();
};

#endif // LIGHTS_HPP 