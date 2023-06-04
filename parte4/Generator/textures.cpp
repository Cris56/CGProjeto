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
void genTexSphere(float radius, int slices, int stacks, Point* dest) {
	int index = 0;
	float height = 1;
	double hstep = 1 / stacks;
	double wstep = 1 / slices;
	for (int i = 0; i < stacks + 1; i++) {
		for (int j = 0; j < slices; j++) {
			dest[index].x = j * wstep;
			dest[index].y = height;
			dest[index].z = 0;
			index++;
		}
		height -= hstep;
	}
}

// aplica por patch
void genTexBezier() { 

}

// aplica em duas partes
void genTexCone(Point* points, int slices, int stacks, Point* dest) {

}
