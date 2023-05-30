#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

struct ponto { float ponto[3]; };

struct Point {
    float x;
    float y;
    float z;
};

struct Triangle {
    Point vertex1;
    Point vertex2;
    Point vertex3;
};

#endif