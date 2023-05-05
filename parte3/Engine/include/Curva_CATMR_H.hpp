#pragma once
#ifndef Curva_CATMR_H
#define Curva_CATMR_H

void makeMatrix(float* x, float* y, float* z, float* m);
void ProdVet(float* a, float* b, float* res);
void multMatrixVector(const float* m, const float* v, float* res);
void normaliza(float* a);
void CMRPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv);

#endif