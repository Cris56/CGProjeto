#include "world.hpp"

World::World() : width(512), height(512), camera(), group() {}

World::World(int w, int h, const Camera& c, const Group& g) : width(w), height(h), camera(c), group(g) {}

int World::getWidth() const {
    return width;
}

int World::getHeight() const {
    return height;
}

const Camera& World::getCamera() const {
    return camera;
}

const Group& World::getGroup() const {
    return group;
}

void World::setWidth(int w) {
    width = w;
}

void World::setHeight(int h) {
    height = h;
}

void World::setCamera(const Camera& c) {
    camera = c;
}

void World::setGroup(const Group& g) {
    group = g;
}

void World::incrementCameraPositionbetaAngle(float angle) {
    camera.incrementPositionbetaAngle(angle);
}

void World::incrementCameraPositionalphaAngle(float angle) {
    camera.incrementPositionalphaAngle(angle);
}

void World::incrementCameraPositionRadius(float radius) {
    camera.incrementPositionRadius(radius);
}