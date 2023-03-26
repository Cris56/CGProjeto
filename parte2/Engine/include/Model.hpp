#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Vector3.hpp"

class Model {
public:
    Model(const std::string &path, const std::string &fileName);
    void readVertices(const std::string& filePath);

    const std::vector<Vector3>& getVertices() const {
        return vertices;
    }

private:
    std::string file;
    std::vector<Vector3> vertices;
};

#endif /* MODEL_HPP */
