#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "point.hpp"

class Model {
public:
    Model(const std::string &path, const std::string &fileName);
    void readVertices(const std::string& filePath);

    const std::vector<Point>& getVertices() const {
        return vertices;
    }

private:
    std::string file;
    std::vector<Point> vertices;
};

#endif /* MODEL_HPP */
