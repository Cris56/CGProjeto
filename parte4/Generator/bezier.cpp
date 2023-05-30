#include "bezier.hpp"

vector<ponto> vBezier;

struct bezier {
	int numpatches = 1;
	vector<vector<int>> patchindex;
	int numcontrol = 4;
	vector<ponto> controlp;
	int numv = 4;
	int tess = 4;
};

bezier b;

void genBezier(float* v) {
	vBezier.resize(b.numv * b.numpatches);
	verticesBezier();
	int j = 0;
	int i = 0;
	int n = b.tess;
	for (int p = 1; p < b.numpatches; p++) {
		for (i = 0; i < b.numv - (n + 1); i++) {
			int indexvB = b.numv * (p-1);
			if ((i + 1) % (n + 1) != 0) {
				v[j] = vBezier[indexvB + i].ponto[0];
				v[j + 1] = vBezier[indexvB + i].ponto[1];
				v[j + 2] = vBezier[indexvB + i].ponto[2];
				j += 3;
				v[j] = vBezier[indexvB + i + 1].ponto[0];
				v[j + 1] = vBezier[indexvB + i + 1].ponto[1];
				v[j + 2] = vBezier[indexvB + i + 1].ponto[2];
				j += 3;
				v[j] = vBezier[indexvB + i + n + 2].ponto[0];
				v[j + 1] = vBezier[indexvB + i + n + 2].ponto[1];
				v[j + 2] = vBezier[indexvB + i + n + 2].ponto[2];
				j += 3;
				v[j] = vBezier[indexvB + i].ponto[0];
				v[j + 1] = vBezier[indexvB + i].ponto[1];
				v[j + 2] = vBezier[indexvB + i].ponto[2];
				j += 3;
				v[j] = vBezier[indexvB + i + n + 2].ponto[0];
				v[j + 1] = vBezier[indexvB + i + n + 2].ponto[1];
				v[j + 2] = vBezier[indexvB + i + n + 2].ponto[2];
				j += 3;
				v[j] = vBezier[indexvB + i + n + 1].ponto[0];
				v[j + 1] = vBezier[indexvB + i + n + 1].ponto[1];
				v[j + 2] = vBezier[indexvB + i + n + 1].ponto[2];
				j += 3;
			}
		}
	}
}

void verticesBezier() {
	int n = b.numpatches;
	for (int i = 0; i < n; i++) {
		vector<ponto> cpoints;
		cpoints.resize(16);
		for (int a = 0; a < 16; a++) {
			int indice = b.patchindex[i][a];
			cpoints[a] = b.controlp[indice];
		}
		curvePoints(cpoints.data(), vBezier.data(), i);
	}
}

void readPatch(const char* filename) {
	string filepath = "../../data/" + string(filename);
	ifstream patch(filepath);
	if (!patch) {
		throw std::runtime_error("Error opening file: " + filepath);
	}

	string line;
	std::getline(patch, line);
	int nump = atoi(line.c_str());
	b.numpatches = nump;

	b.patchindex.resize(nump);
	for (int i = 0; i < nump; i++) {
		string patch_line;
		std::getline(patch, patch_line);
		string index;
		istringstream s(patch_line);
		while (std::getline(s, index, ',')) {
			b.patchindex[i].push_back(stoi(index));
		}
		s.clear();
	}

	std::getline(patch, line);
	int numc = atoi(line.c_str());
	b.numcontrol = numc;

	b.controlp.resize(numc);
	
	for (int a = 0; a < numc; a++) {
		std::getline(patch, line);
		istringstream p(line);
		string coordenada;
		for (int j = 0; std::getline(p, coordenada, ','); j++) {
			b.controlp[a].ponto[j] = stof(coordenada);
		}
		
		p.clear();
	}

	if (patch.fail()) {
		throw runtime_error("Error reading file: " + filepath);
	}

	patch.close();
}

int numvtBezier(int tess) {
	b.numv = (tess + 1) * (tess + 1);
	b.tess = tess;
	return tess * tess * 2 * 3 * (b.numpatches-1);
}

// adaptado de https: //pomax.github.io/bezierinfo/#decasteljau
float castjau(float* points, float ratio, int nump) {
	float t = ratio;
	if (nump == 1) {
		return points[0];
	}
	else {
		float newpoints[4];
		for (int i = 0; i < nump - 1; i++) {
			float p = (1 - t) * points[i] + t * points[i + 1];
			newpoints[i] = p;
		}
		return castjau(newpoints, t, nump - 1);
	}
}

void curvePoints(ponto* points, ponto* v, int patch) {
	int tess = b.tess;
	float r = 1.0f / tess;
	int index = patch*(tess+1)*(tess+1);

	vector<ponto> ci1; ci1.resize(4);
	vector<ponto> ci2; ci2.resize(4);
	vector<ponto> ci3; ci3.resize(4);
	vector<ponto> ci4; ci4.resize(4);
	
	for (int i = 0; i < 4; i++) {
		ci1[i] = points[i];
		ci2[i] = points[i + 4];
		ci3[i] = points[i + 8];
		ci4[i] = points[i + 12];
	}

	vector<ponto> cm1; cm1.resize(tess + 1);
	cm1[0] = ci1[0]; cm1[tess] = ci1[3];
	vector<ponto> cm2; cm2.resize(tess + 1);
	cm2[0] = ci2[0]; cm2[tess] = ci2[3];
	vector<ponto> cm3; cm3.resize(tess + 1);
	cm3[0] = ci3[0]; cm3[tess] = ci3[3];
	vector<ponto> cm4; cm4.resize(tess + 1);
	cm4[0] = ci4[0]; cm4[tess] = ci4[3];

	for (int j = 1; j < tess; j++) {
		ponto p1, p2, p3, p4;
		float xlist1[4]; float ylist1[4]; float zlist1[4];
		float xlist2[4]; float ylist2[4]; float zlist2[4];
		float xlist3[4]; float ylist3[4]; float zlist3[4];
		float xlist4[4]; float ylist4[4]; float zlist4[4];

		for (int k = 0; k < 4; k++) {
			xlist1[k] = ci1[k].ponto[0];
			ylist1[k] = ci1[k].ponto[1];
			zlist1[k] = ci1[k].ponto[2];

			xlist2[k] = ci2[k].ponto[0];
			ylist2[k] = ci2[k].ponto[1];
			zlist2[k] = ci2[k].ponto[2];

			xlist3[k] = ci3[k].ponto[0];
			ylist3[k] = ci3[k].ponto[1];
			zlist3[k] = ci3[k].ponto[2];

			xlist4[k] = ci4[k].ponto[0];
			ylist4[k] = ci4[k].ponto[1];
			zlist4[k] = ci4[k].ponto[2];
		}

		float x1 = castjau(xlist1, r * j, 4); p1.ponto[0] = x1;
		float x2 = castjau(xlist2, r * j, 4); p2.ponto[0] = x2;
		float x3 = castjau(xlist3, r * j, 4); p3.ponto[0] = x3;
		float x4 = castjau(xlist4, r * j, 4); p4.ponto[0] = x4;

		float y1 = castjau(ylist1, r * j, 4); p1.ponto[1] = y1;
		float y2 = castjau(ylist2, r * j, 4); p2.ponto[1] = y2;
		float y3 = castjau(ylist3, r * j, 4); p3.ponto[1] = y3;
		float y4 = castjau(ylist4, r * j, 4); p4.ponto[1] = y4;

		float z1 = castjau(zlist1, r * j, 4); p1.ponto[2] = z1;
		float z2 = castjau(zlist2, r * j, 4); p2.ponto[2] = z2;
		float z3 = castjau(zlist3, r * j, 4); p3.ponto[2] = z3;
		float z4 = castjau(zlist4, r * j, 4); p4.ponto[2] = z4;

		cm1[j] = p1; cm2[j] = p2; cm3[j] = p3; cm4[j] = p4;
	}

	for (int l = 0; l < tess + 1; l++) {
		vector<ponto> curva;
		curva.resize(tess + 1);
		curva[0] = cm1[l];
		curva[tess] = cm4[l];

		float xlist[4]; float ylist[4]; float zlist[4];

		xlist[0] = cm1[l].ponto[0];
		xlist[1] = cm2[l].ponto[0];
		xlist[2] = cm3[l].ponto[0];
		xlist[3] = cm4[l].ponto[0];

		ylist[0] = cm1[l].ponto[1];
		ylist[1] = cm2[l].ponto[1];
		ylist[2] = cm3[l].ponto[1];
		ylist[3] = cm4[l].ponto[1];

		zlist[0] = cm1[l].ponto[2];
		zlist[1] = cm2[l].ponto[2];
		zlist[2] = cm3[l].ponto[2];
		zlist[3] = cm4[l].ponto[2];

		for (int m = 1; m < tess; m++) {
			ponto p;
			float x = castjau(xlist, r * m, 4);
			float y = castjau(ylist, r * m, 4);
			float z = castjau(zlist, r * m, 4);

			p.ponto[0] = x; p.ponto[1] = y; p.ponto[2] = z;
			curva[m] = p;
		}

		for (int n = 0; n < tess + 1; n++) {
			v[index + n] = curva[n];
		}

		index += tess + 1;
		curva.clear();
	}

	ci1.clear(); ci2.clear(); ci3.clear(); ci4.clear();
	cm1.clear(); cm2.clear(); cm3.clear(); cm4.clear();
}