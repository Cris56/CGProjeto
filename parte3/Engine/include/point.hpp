#ifndef POINT_HPP
#define POINT_HPP

class Point {

public:
    Point(double x, double y, double z);
    double getX() const;
    double getY() const;
    double getZ() const;
    double getRadius() const;
    double getalpha() const;
    double getbeta() const;
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);
    void incrementRadius(double deltaR);
    void incrementbeta(double deltabeta);
    void incrementalpha(double deltaalpha);
    void printSphericalCoordinates() const;
    void printCartesianCoordinates() const;
    
private:
    double x, y, z;
    void spherical2Cartesian(double r, double beta, double alpha);
};

#endif // POINT_HPP
