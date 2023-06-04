#ifndef WORLD_HPP
#define WORLD_HPP

#include "camera.hpp"
#include "group.hpp"

class World {
public:
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
    void incrementCameraPositionbetaAngle(float angle);
    void incrementCameraPositionalphaAngle(float angle);
    void incrementCameraPositionRadius(float radius);

private:
    int width;
    int height;
    Camera camera;
    Group group;
};

#endif // WORLD_HPP
