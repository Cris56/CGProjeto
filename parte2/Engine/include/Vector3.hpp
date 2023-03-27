#ifndef VECTOR3_HPP
#define VECTOR3_HPP

class Vector3 {
public:

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    float getX() const;
    float getY() const;
    float getZ() const;
    void setVector3(float x, float y, float z);
    void setX(float x);
    void setY(float y);
    void setZ(float z);

private:
    float x;
    float y;
    float z;
};

#endif // VECTOR3_HPP
