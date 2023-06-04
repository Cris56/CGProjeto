#include <cmath>
#include "Curva_CATMR_H.hpp"
#include <stdio.h>

void makeMatrix(float* x, float* y, float* z, float* m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void ProdVet(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

void normaliza(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    if (l != 0) {
        a[0] = a[0] / l;
        a[1] = a[1] / l;
        a[2] = a[2] / l;
    }
}


// multiplicar matriz por vetor 
void multMatrixVector(const float* m, const float* v, float* res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}

void CMRPoint(float t, Point p0, Point p1, Point p2, Point p3, float* pos, float* deriv) {
    float m[4][4] = {
        {-0.5f, 1.5f, -1.5f, 0.5f},
        {1.0f, -2.5f, 2.0f, -0.5f},
        {-0.5f, 0.0f, 0.5f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f}
    };

    float px[4] = { static_cast<float>(p0.getX()), static_cast<float>(p1.getX()), static_cast<float>(p2.getX()), static_cast<float>(p3.getX()) };
    float py[4] = { static_cast<float>(p0.getY()), static_cast<float>(p1.getY()), static_cast<float>(p2.getY()), static_cast<float>(p3.getY()) };
    float pz[4] = { static_cast<float>(p0.getZ()), static_cast<float>(p1.getZ()), static_cast<float>(p2.getZ()), static_cast<float>(p3.getZ()) };

    float a[4], px_a[4], py_a[4], pz_a[4];
    multMatrixVector(*m, px, px_a);
    multMatrixVector(*m, py, py_a);
    multMatrixVector(*m, pz, pz_a);

    pos[0] = t * t * t * px_a[0] + t * t * px_a[1] + t * px_a[2] + px_a[3];
    pos[1] = t * t * t * py_a[0] + t * t * py_a[1] + t * py_a[2] + py_a[3];
    pos[2] = t * t * t * pz_a[0] + t * t * pz_a[1] + t * pz_a[2] + pz_a[3];

    deriv[0] = 3 * t * t * (px_a[0] - px_a[1]) + 2 * t * (px_a[1] - px_a[2]) + (px_a[2] - px_a[3]);
    deriv[1] = 3 * t * t * (py_a[0] - py_a[1]) + 2 * t * (py_a[1] - py_a[2]) + (py_a[2] - py_a[3]);
    deriv[2] = 3 * t * t * (pz_a[0] - pz_a[1]) + 2 * t * (pz_a[1] - pz_a[2]) + (pz_a[2] - pz_a[3]);
}
