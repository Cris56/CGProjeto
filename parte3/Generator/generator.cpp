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

        if (strcmp(argv[1], "DEBUG") == 0) {

            vector<float> PlaneVertices;
            const int numvtPlane = (6 * 3 * 3);
            PlaneVertices.resize(numvtPlane * 3);
            genPlane(1, 3, PlaneVertices.data());
            save_vertices_to_file("plane_2_3.3d", PlaneVertices);

            vector<float> BoxVertices;
            const int numv = (48 * 3 * 3) + (12 * 3) - 24;
            BoxVertices.resize(numv * 3);
            genBox(2, 3, BoxVertices.data());
            save_vertices_to_file("box_2_3.3d", BoxVertices);

            vector<float> SphereVertices;
            const int numvt = 6 * 10 * 10;
            SphereVertices.resize(numvt * 3);
            genSphere(1, 10, 10, SphereVertices.data());
            save_vertices_to_file("sphere_1_10_10.3d", SphereVertices);
                
            vector<float> ConeVertices;
            int triangulosBase = 4 + 1;
            int triangulosBody = 4 * 3 * 2;
            ConeVertices.resize((triangulosBase + triangulosBody) * 9);
            genCone(1, 2, 4, 3, ConeVertices.data());
            save_vertices_to_file("cone_1_2_4_3.3d", ConeVertices);

            

            return 0;
        }

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
            const int numvt = 6 * a2 * a3;
            vertices.resize(numvt * 3);
            genSphere(a1, a2, a3, vertices.data());
        }
        else if (!strcmp(obj.c_str(), "box") && argc == 5) {
            const int numv = (48 * a2 * a2) + (12 * a2) - 24;
            vertices.resize(numv * 3);
            genBox(a1, a2, vertices.data());
        }
        else if (!strcmp(obj.c_str(), "cone") && argc == 7) {
            const int a3 = atoi(argv[4]);
            const int a4 = atoi(argv[5]);
            int triangulosBase = a3 + 1;
            int triangulosBody = a3 * a4 * 2;
            vertices.resize((triangulosBase + triangulosBody) * 9);
            genCone(a1, a2, a3, a4, vertices.data());
        }
        else if (!strcmp(obj.c_str(), "plane") && argc == 5) {
            const int numvt = (6 * a2 * a2);
            vertices.resize(numvt * 3);
            genPlane(a1, a2, vertices.data());
        }
        else {
            throw invalid_argument("Invalid object or corresponding parameters.");
        }

        save_vertices_to_file(fd, vertices);
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        cerr << "Usage: [sphere|box|cone|plane] arg1 arg2 [arg3 arg4] outputfile" << endl;
        cerr << "    - sphere: generate a sphere with given radius, slices, and stacks" << endl;
        cerr << "        Usage: sphere [radius] [slices] [stacks] [output file]" << endl;
        cerr << "        Example: sphere 1 10 10 sphere.3d" << endl;
        cerr << "    - box: generate a box with given length and grid divisions" << endl;
        cerr << "        Usage: box [length] [divisions] [output file]" << endl;
        cerr << "        Example: box 2 3 box.3d" << endl;
        cerr << "    - cone: generate a cone with given radius, height, slices, and stacks" << endl;
        cerr << "        Usage: cone [radius] [height] [slices] [stacks] [output file]" << endl;
        cerr << "        Example: cone 1 2 4 3 cone.3d" << endl;
        cerr << "    - plane: generate a plane with given length and grid divisions" << endl;
        cerr << "        Usage: plane [length] [divisions] [output file]" << endl;
        cerr << "        Example: plane 1 3 plane.3d" << endl;
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
