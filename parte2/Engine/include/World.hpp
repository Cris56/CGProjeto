#ifndef WORLD_HPP
#define WORLD_HPP

#include "Camera.hpp"
#include "Group.hpp"

class World {
public:
    int width;
    int height;
    Camera camera;
    Group group;

    World();
    World(int w, int h, const Camera &c, const Group &g);
    int getWidth() const;
    int getHeight() const;
    const Camera &getCamera() const;
    const Group &getGroup() const;
    void setWidth(int w);
    void setHeight(int h);
    void setCamera(const Camera &c);
    void setGroup(const Group &g);
};

#endif // WORLD_HPP
