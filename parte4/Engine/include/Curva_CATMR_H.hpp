#ifndef CURVA_CATMR_H
#define CURVA_CATMR_H

#include "point.hpp"

void makeMatrix(float* x, float* y, float* z, float* m);
void ProdVet(float* a, float* b, float* res);
void multMatrixVector(const float* m, const float* v, float* res);
void normaliza(float* a);
void CMRPoint(float t, Point p0, Point p1, Point p2, Point p3, float *pos, float *deriv);

#endif