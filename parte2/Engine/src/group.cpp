#include "group.hpp"

Group::Group() {}

void Group::addGroup(const Group& g) {
    groups.push_back(g);
}

void Group::addModel(const Model& m) {
    models.push_back(m);
}

Transform Group::getTransform() const {
    return transform;
}

void Group::setTransform(const Transform& t) {
    transform = t;
}

