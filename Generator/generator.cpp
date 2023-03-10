#include "generator.h"

void save_vertices_to_file(const char* filename, const vector<float>& vertices) {
    string filepath = "../../data/" + string(filename);
    ofstream outfile(filepath);
    if (!outfile) {
        throw runtime_error("Error opening file: " + filepath);
    }
    
    outfile << vertices.size() / 3 << '\n';
    for (size_t i = 0; i < vertices.size(); i += 3) {
        outfile << vertices[i] << ' ' << vertices[i + 1] << ' ' << vertices[i + 2] << '\n';
    }

    if (outfile.fail()) {
        throw runtime_error("Error writing to file: " + filepath);
    }

    outfile.close();
}

int main(int argc, char** argv) {
    try {
    if (argc < 5 || argc > 7) {
        throw invalid_argument("Invalid number of arguments");
    }

    const string obj = argv[1];
    const float a1 = atof(argv[2]);
    const int a2 = atoi(argv[3]);
    const char* fd = argv[argc - 1];

    vector<float> vertices;

    if (!strcmp(obj.c_str(), "sphere") && argc == 6) {
        const int a3 = atoi(argv[4]);
        const int numvt = 6* a2 * a3;
        vertices.resize(numvt * 3);
        genSphere(a1, a2, a3, vertices.data());
    }
    else if (!strcmp(obj.c_str(), "box") && argc == 5) {
        vertices.resize(24);
        genBox(a1, a2, vertices.data());
    }
    else if (!strcmp(obj.c_str(), "cone") && argc == 7) {
        const int a3 = atoi(argv[4]);
        const int a4 = atoi(argv[5]);
        vertices.resize(33 * 3);
        genCone(a1, a2, a3, a4, vertices.data());
    }
    else if (!strcmp(obj.c_str(), "plane") && argc == 5) {
        vertices.resize((a2 + 1) * (a2 + 1) * 3);
        genPlane(a1, a2, vertices.data());
    }
    else {
        throw invalid_argument("Invalid object or corresponding parameters.");
    }

        save_vertices_to_file(fd, vertices);
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        cerr << "Usage: " << argv[0] << " [sphere|box|cone|plane] arg1 arg2 [arg3 arg4] outputfile" << endl;
        return 1;
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
