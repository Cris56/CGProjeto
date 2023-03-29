#include <iostream>
#include <cmath>
#include "point.hpp"

// Constructor that receives x, y, and z
Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

// Getters and setters for x, y, z, radius, alpha, and beta
double Point::getX() const { return x; }
double Point::getY() const { return y; }
double Point::getZ() const { return z; }
void Point::setX(double newX) { x = newX; }
void Point::setY(double newY) { y = newY; }
void Point::setZ(double newZ) { z = newZ; }

double Point::getRadius() { return sqrt(x*x + y*y + z*z); }

double Point::getalpha() { return atan2(x, z); }

double Point::getbeta() { return M_PI/2 - acos(y/sqrt(x*x + y*y + z*z)); }

// Increment functions
void Point::incrementRadius(double deltaRadius) {
    double currentRadius = std::sqrt(x*x + y*y + z*z);
    double currentBeta = getbeta();
    double currentAlpha = getalpha();
    double newRadius = currentRadius + deltaRadius;
    spherical2Cartesian(newRadius, currentBeta, currentAlpha);
}

void Point::incrementbeta(double deltaBeta) {
    double currentRadius = getRadius();
    double currentBeta = getbeta();
    double currentAlpha = getalpha();
    double newBeta = currentBeta + deltaBeta;
    if (newBeta > 1.5) {
        newBeta = 1.5;
    } else if (newBeta < -1.5) {
        newBeta = -1.5;
    }
    spherical2Cartesian(currentRadius, newBeta, currentAlpha);
}

void Point::incrementalpha(double deltaalpha) {
    double currentRadius = getRadius();
    double currentAlpha = getalpha();
    double currentBeta = getbeta();
    double newalpha = currentAlpha + deltaalpha;
    spherical2Cartesian(currentRadius, currentBeta, newalpha);
}

// Print functions
void Point::printSphericalCoordinates() const {
    double radius = std::sqrt(x*x + y*y + z*z);
    double alpha = atan2(x, z);
    double beta = M_PI/2 - acos(y/sqrt(x*x + y*y + z*z));
    std::cout << "r = " << radius << ", beta = " << beta << ", alpha = " << alpha << std::endl;
}

void Point::printCartesianCoordinates() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

void Point::spherical2Cartesian(double radius, double beta, double alpha) {
	x = radius * cos(beta) * sin(alpha);
	y = radius * sin(beta);
	z = radius * cos(beta) * cos(alpha);
}
