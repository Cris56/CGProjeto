#ifndef PONTO_HPP
#define PONTO_HPP

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

struct triangle {
	ponto p1;
	ponto p2;
	ponto p3;
};

#endif