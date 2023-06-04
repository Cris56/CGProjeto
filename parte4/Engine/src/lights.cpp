#include "lights.hpp" 

Light::Light(Type type, Point pos) {
    Light::type = type;
    Light::pos = pos;
    Light::cutoff = -1;
}

Light::Light(Point pos, Point dir, int cutoff) {
    Light::type = SPOTLIGHT;
    Light::pos = pos;
    Light::dir = dir;
    Light::cutoff = cutoff;
}

Point Light::getPosition() {
    return Light::pos;
}

Point Light::getDirection() {
    return Light::dir;
}

int Light::getCutoff() {
    return Light::cutoff;
}

void Light::render() {
    GLfloat ambiente [4] = {1.0,1.0,1.0,1.0};
    GLfloat diff     [4] = {1.0,1.0,1.0,0.0};
    GLfloat spec     [4] = {1.0,1.0,1.0,1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

    float pose[4] = {pos.getX(), pos.getY(), pos.getZ(), type == POINT || type == SPOTLIGHT ? 1.0f : 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, pose);

    if(type == SPOTLIGHT) {
        float dire[3] = {dir.getX(), dir.getY(), dir.getZ()};
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dire);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
    }
}