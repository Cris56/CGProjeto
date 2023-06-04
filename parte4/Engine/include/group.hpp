#ifndef GROUP_HPP
#define GROUP_HPP

#include <vector>
#include "transform.hpp"
#include "model.hpp"
#include "colours.hpp"
#include "lights.hpp"

class Group {
public:
    std::vector<Group> groups;
    std::vector<Model> models;

    Group();

    void addGroup(const Group &g);
    void addModel(const Model &m);
    Transform getTransform() const;
    void setTransform(const Transform &t);

private:
    Transform transform;
};

#endif // GROUP_HPP
