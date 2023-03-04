#include "generator.h"

int main(int argc, char** argv) {
    if (argc < 5 || argc > 7) printf("Invalid number of arguments.\n");
    else {
        // Argumentos comuns a todos
        char* obj = argv[1];
        float a1 = atof(argv[2]);
        int a2 = atoi(argv[3]);
        char* fd = argv[argc - 1];
        // Abrir ficheiro
        ofstream fich(fd);
        
        if (fich.is_open()) {
            if ( argc == 6) { //strcmp(obj, "sphere") &&
                int a3 = atoi(argv[4]);
                int numv = a2 * (a3 + 1);
                float *vertices = (float*) malloc(sizeof(float)*3*numv);
                genSphere(a1, a2, a3, vertices);
                fich << numv << "\n";
                for (int i = 0; i < numv * 3; i++) {
                    if (i % 3 == 0) fich << "\n";
                    fich << vertices[i] << " ";
                }
            }
            else if (obj == "box" && argc == 5) {

            }
            else if (obj == "cone" && argc == 7) {
                int a3 = atoi(argv[4]);
                int a4 = atoi(argv[5]);
            }
            else if (obj == "plane" && argc == 5) {

            }
            else printf("Invalid object or corresponding parameters.\n");
        }
        else printf("Error opening file");

        // Fechar ficheiro
        fich.close();
    }
    return 0;
}

void genSphere(float radius, int slices, int stacks, float *v) {
    int n = slices;
    int m = stacks;


    for (int i = 0; i < (m+1); i++) {
        float av = (M_PI/2) - i * (M_PI / m);
        float y = radius * sin(av);
        for (int j = 0; j < n; j++) {
            float ah = j * (2 * M_PI / n);
            float x = radius * sin(ah) * cos(av);
            float z = radius * cos(ah) * cos(av);

            if (y == radius || y == -radius) {
                v[(3 * n * i) + (3 * j)] = 0.0;
                v[(3 * n * i) + (3 * j) + 1] = y;
                v[(3 * n * i) + (3 * j) + 2] = 0.0;
            }
            else {
                v[(3 * n * i) + (3 * j)] = x;
                v[(3 * n * i) + (3 * j) + 1] = y;
                v[(3 * n * i) + (3 * j) + 2] = z;
            }
        }
    }
}
