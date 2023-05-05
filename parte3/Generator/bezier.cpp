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
		int numcont2 = (b.tess+1) * 4;
		vector<ponto> control2;
		control2.resize(numcont2);
		curvePoints(cpoints.data(), control2.data(), 0, 16, 4);
		vector<ponto> cpoints2;
		cpoints2.resize(numcont2);
		int indcp2 = 0;
		for (int j = 0; j < b.tess; j++) {
			for (int k = 0; k < 4; k++) {
				cpoints2[indcp2+k] = control2[j+k*b.tess];
			}
			indcp2 += 4;
		}
		curvePoints(cpoints2.data(), vBezier.data(), i, numcont2, b.tess+1);
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
	b.numv = tess * tess;
	b.tess = tess;
	return tess * tess * 2 * 3 * b.numpatches;
}

void curvePoints(ponto* points, ponto* v, int patch, int numcp, int curvas) {
	vector<ponto> pcurvas;
	int numcurvas = curvas;
	pcurvas.resize(numcp);
	int indv = 0;
	if (patch > 0) {
		indv = b.numv * patch;
	}
	float r = 1.0f / b.tess;
	float rdiff = r;
	for (int j = 0; j < numcp; j+=4) {
		ponto p;
		float xlist[4];
		float ylist[4];
		float zlist[4];
		for (int l = 0; l < 4; l++) {
			xlist[l] = points[j+l].ponto[0];
			ylist[l] = points[j+l].ponto[1];
			zlist[l] = points[j+l].ponto[2];
		}
		for (int m = 0; m < b.tess+1; m++) {
			float x = castjau(xlist, rdiff, 4);
			float y = castjau(ylist, rdiff, 4);
			float z = castjau(zlist, rdiff, 4);
			rdiff += r;

			p.ponto[0] = x;
			p.ponto[1] = y;
			p.ponto[2] = z;

			v[indv] = p;
			indv++;
		}
		
	}
}

// adaptado de https: //pomax.github.io/bezierinfo/#decasteljau
float castjau(float* points, float ratio, int nump) {
	float t = ratio;
	float ret = 0;
	if (nump == 1) {
		ret = points[0];
	}
	else {
		float newpoints[4];
		for (int i = 0; i < nump-1; i++) {
			float p = (1 - t) * points[i] + t * points[i + 1];
			newpoints[i] = p;
		}
		ret = castjau(newpoints, t, nump - 1);
	}
	return ret;
}