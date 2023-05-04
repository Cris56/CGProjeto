#include "bezier.hpp"

vector<pontos> vBezier;

struct bezier {
	int numpatches = 1;
	vector<vector<int>> patchindex;
	int numcontrol = 4;
	vector<pontos> controlp;
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
	 for (i = 0; i < b.numv - (n + 1); i++) {
		if ((i + 1) % (n + 1) != 0) {
			v[j] = vBezier[i].ponto[0];
			v[j + 1] = vBezier[i].ponto[1];
			v[j + 2] = vBezier[i].ponto[2];
			j += 3;
			v[j] = vBezier[i + 1].ponto[0];
			v[j + 1] = vBezier[i + 1].ponto[1];
			v[j + 2] = vBezier[i + 1].ponto[2];
			j += 3;
			v[j] = vBezier[i + n + 2].ponto[0];
			v[j + 1] = vBezier[i + n + 2].ponto[1];
			v[j + 2] = vBezier[i + n + 2].ponto[2];
			j += 3;
			v[j] = vBezier[i].ponto[0];
			v[j + 1] = vBezier[i].ponto[1];
			v[j + 2] = vBezier[i].ponto[2];
			j += 3;
			v[j] = vBezier[i + n + 2].ponto[0];
			v[j + 1] = vBezier[i + n + 2].ponto[1];
			v[j + 2] = vBezier[i + n + 2].ponto[2];
			j += 3;
			v[j] = vBezier[i + n + 1].ponto[0];
			v[j + 1] = vBezier[i + n + 1].ponto[1];
			v[j + 2] = vBezier[i + n + 1].ponto[2];
			j += 3;
		}
	}
}

void verticesBezier() {
	for (int i = 0; i < b.numpatches; i++) {
		
		 pontos cpoints[16];
		 for (int a = 0; a < 16; a++) {
		 	int indice = b.patchindex[i][a];
		 	cpoints[a] = b.controlp[indice];
		}
		int numcont2 = b.tess * 4;
		vector<pontos> control2;
		control2.resize(numcont2);
		curvePoints(cpoints, control2.data(), 0);
		curvePoints(control2.data(), vBezier.data(), i);
	}
}

void readPatch(const char* filename) {
	string filepath = /*"../../data/" + */string(filename);
	ifstream patch(filepath);
	if (!patch) {
		throw std::runtime_error("Error opening file: " + filepath);
	}
	
	string line;
	getline(patch, line);
	int nump = atoi(line.c_str());
	b.numpatches = nump;

	b.patchindex.resize(nump);
	for (int i = 0; i < nump; i++) {
		string patch_line;
		getline(patch,patch_line);
		string index;
		istringstream s(patch_line);
		while (getline(s,index,',')) {
			b.patchindex[i].push_back(stoi(index));
		}
		s.clear();
	}



	 getline(patch, line);
	 int numc = atoi(line.c_str());
	 b.numcontrol = numc;

	 b.controlp.resize(numc);
	
	for (int a = 0; a < numc; a++) {
		getline(patch, line);
		istringstream p(line);
		string coordenada;
		float x, y, z;
		for(int j = 0;getline(p,coordenada,',');j++) {
			b.controlp[a].ponto[j]= stof(coordenada);
		}
		p.clear();
	}
	

	if (patch.fail()) {
		throw runtime_error("Error reading file: " + filepath);
	}
	
	patch.close();
}

int numvtBezier(int tess) {
	b.numv = tess*tess;
	b.tess = tess;
	return tess * tess * 2 * 3;
}


void curvePoints(pontos* points, pontos* v, int patch) {
	float p1[4];
	float p2[4];
	float p3[4];
	float p4[4];
	int indv = b.numv*patch;
	float r = 1.0 / b.tess;
	for (int p = 0; p < 3; p++) {
		for (int i = 0; i < 4; i++) {
			p1[i] = points[i].ponto[p];
			p2[i] = points[i + 4].ponto[p];
			p3[i] = points[i + 8].ponto[p];
			p4[i] = points[i + 12].ponto[p];
		}
 		for (int j = 0; j < b.tess; j++) {
			float a = castjau(p1, j * r, 4);
			float b = castjau(p2, j * r, 4);
			float c = castjau(p3, j * r, 4);
			float d = castjau(p4, j * r, 4);
	 		v[indv].ponto[p] = a;
			v[indv + 1].ponto[p] = b;
			v[indv + 2].ponto[p] = c;
			v[indv + 3].ponto[p] = d;
			indv += 4;
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