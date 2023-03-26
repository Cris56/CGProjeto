#ifndef GROUP_HPP
#define GROUP_HPP

#include <vector>
#include "Transform.hpp"
#include "Model.hpp"

class Group {
public:
    std::vector<Group> groups;
    std::vector<Transform> transforms;
    std::vector<Model> models;

    Group();
};

#endif // GROUP_HPP
