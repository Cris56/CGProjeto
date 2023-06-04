#include "colours.hpp"

float Color::getR() {
    return Color::r;
}

float Color::getG() {
    return Color::g;
}

float Color::getB() {
    return Color::b;
}

float * ModelColor::getDiffuse() {
    return ModelColor::diffuse;
}
        
float * ModelColor::getAmbient() {
    return ModelColor::ambient;
}

float * ModelColor::getSpecular() {
    return ModelColor::specular;
}

float * ModelColor::getEmission() {
    return ModelColor::emission;
}

float ModelColor::getShininess() {
    return ModelColor::shininess;
}