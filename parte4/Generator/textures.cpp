#include "textures.hpp"

// aplica por todo
void genTexPlane(Point* points, int div, float size, Point* dest) {
	int numv = (div + 1) * (div + 1) * 6;
	float s = size / 2;
	// se size = x, o ponto 0 é o -x/2
	for (int i = 0; i < numv; i++) {
		dest[i].x = (points[i].x + s) / size;
		dest[i].y = (points[i].z + s) / size;
		dest[i].z = 0;
	}
}

// aplica por face
void genTexBox(Point* points, float size, int div, Point* dest) {
	int numvFace = (div + 1) * (div + 1);
	float s = size / 2;
	// frente e trás
	for (int i = 0; i < numvFace * 2; i++) {
		dest[i].x = (points[i].x + s) / size;
		dest[i].y = (points[i].y + s) / size;
		dest[i].z = 0;
	}
	// lados
	for (int i = numvFace * 2; i < numvFace * 4; i++) {
		dest[i].x = (points[i].z + s) / size;
		dest[i].y = (points[i].y + s) / size;
		dest[i].z = 0;
	}
	// cima e baixo
	for (int i = numvFace * 4; i < numvFace * 6; i++) {
		dest[i].x = (points[i].x + s) / size;
		dest[i].y = (points[i].z + s) / size;
		dest[i].z = 0;
	}
}

// aplica por todo, arredondando
void genTexSphere(int slices, int stacks, Point* dest) {
	int index = 0;
	float hstep = 1 / (float) stacks;
	float wstep = 1 / (float) slices;
	for (int i = 0; i < (stacks + 1); i++) {
		float y = (stacks - i) * hstep;
		for (int j = 0; j < slices; j++) {
			float x = j * wstep;
			dest[index].x = x;
			dest[index].y = y;
			dest[index].z = 0;
			index++;
		}
	}


}

// aplica por patch
void genTexBezier(int tess, int patches, Point* dest) {
	int numvp = (tess + 1) * (tess + 1);
	float step = 1 / (float) tess;
	int index = 0;
	for (int i = 0; i < patches; i++) {
		for (int j = 0; j < tess + 1; j++) {
			float x = j * step;
			for (int k = 0; k < tess; k++) {
				float y = k * step;
				dest[index].x = x;
				dest[index].y = y;
				dest[index].z = 0;
				index++;
			}
		}
	}
}

// aplica por slice
void genTexCone(int slices, int stacks, Point* dest) {
	int numvBase = (slices + 1) * 3;
	int	numvBody = slices * stacks * 2 * 3;
	for (int i = 0; i < numvBase; i+=3) {
		dest[i].x = 0;
		dest[i].y = 0;
		dest[i].z = 0;

		dest[i + 1].x = 0;
		dest[i + 1].y = 1;
		dest[i + 1].z = 0;

		dest[i + 2].x = 1;
		dest[i + 2].y = 1;
		dest[i + 2].z = 0;
	}
	for (int j = numvBase; j < (numvBody + numvBase); j+=6) {
		dest[j].x = 0;
		dest[j].y = 0;
		dest[j].z = 0;

		dest[j + 1].x = 1;
		dest[j + 1].y = 1;
		dest[j + 1].z = 0;

		dest[j + 2].x = 0;
		dest[j + 2].y = 1;
		dest[j + 2].z = 0;
		
		dest[j + 3].x = 0;
		dest[j + 3].y = 0;
		dest[j + 3].z = 0;

		dest[j + 4].x = 1;
		dest[j + 4].y = 0;
		dest[j + 4].z = 0;

		dest[j + 5].x = 1;
		dest[j + 5].y = 1;
		dest[j + 5].z = 0;
	}
}
