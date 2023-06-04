#include "point.hpp"

// Constructor that receives x, y, and z
Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

// Getters and setters for x, y, z, radius, alpha, and beta
double Point::getX() const { return x; }
double Point::getY() const { return y; }
double Point::getZ() const { return z; }
double Point::getRadius() const { return sqrt(x*x + y*y + z*z); }
double Point::getalpha() const { return std::atan2(x, z); }
double Point::getbeta() const { return M_PI/2 - std::acos(y/std::sqrt(x*x + y*y + z*z)); }
void Point::setX(double newX) { x = newX; }
void Point::setY(double newY) { y = newY; }
void Point::setZ(double newZ) { z = newZ; }

// Increment functions
void Point::incrementRadius(double deltaRadius) {
    double currentRadius = getRadius();
    double currentBeta = getbeta();
    double currentAlpha = getalpha();
    double newRadius = currentRadius + deltaRadius;
    if (newRadius <= 0) newRadius = std::numeric_limits<double>::epsilon();
    spherical2Cartesian(newRadius, currentBeta, currentAlpha);
}

void Point::incrementbeta(double deltaBeta) {
    double currentRadius = getRadius();
    double currentBeta = getbeta();
    double currentAlpha = getalpha();
    double newBeta = currentBeta + deltaBeta;
    if (newBeta > M_PI/2) {
        newBeta = M_PI/2;
    } else if (newBeta < -M_PI/2) {
        newBeta = -M_PI/2;
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
    double radius = getRadius();
    double alpha = atan2(x, z);
    double beta = M_PI/2 - acos(y/sqrt(x*x + y*y + z*z));
    std::cout << "Spherical coordinates: r = " << radius << ", beta = " << beta << ", alpha = " << alpha << std::endl;
}

void Point::printCartesianCoordinates() const {
    std::cout << "Cartesian coordinates: (" << x << ", " << y << ", " << z << ")" << std::endl;
}

void Point::spherical2Cartesian(double radius, double beta, double alpha) {
	x = radius * cos(beta) * sin(alpha);
	y = radius * sin(beta);
	z = radius * cos(beta) * cos(alpha);
}
