#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "point.hpp"
#include "GL/glew.h"
#include "GL/gl.h"

class Model {
public:
    Model(const std::string& path, const std::string& fileName);
    const std::vector<Point>& getVertices() const;
    const std::vector<float> getVBO() const;

private:
    void readVertices(const std::string& filePath);
    void prepareData();
    std::string file;
    std::vector<Point> vertices;
    std::vector<float> vbo;
    std::vector<GLuint> vbos;
};

#endif /* MODEL_HPP */
