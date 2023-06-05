#ifndef CURVA_CATMR_H
#define CURVA_CATMR_H

#include "point.hpp"

#include <vector>
#include <cmath>
#include <stdio.h>
#include <GL/glew.h>
#include <cstring>


void makeMatrix(float* x, float* y, float* z, float* m);
void ProdVet(float* a, float* b, float* res);
void multMatrixVector(const float* m, const float* v, float* res);
void normaliza(float* a);
void buildRotMatrix(float* x, float* y, float* z, float* m);
float length(float* v);
void CMRPoint(float t, Point p0, Point p1, Point p2, Point p3, float *pos, float *deriv);
void renderCatmullRomCurve(const std::vector<Point>& pontos, int TAMANHO, float TESSELATION, float* curve_length);
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, const std::vector<Point>& t, int TAMANHO);

#endif