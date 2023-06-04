#ifndef COLOURS_HPP
#define COLOURS_HPP

class Color {
    private:
        float r, g, b;

    public:
        Color() {
            Color::r = 0.5;
            Color::g = 0.5;
            Color::b = 0.5;
        }

        Color(float i, float j, float u) {
            Color::r = i;
            Color::g = j;
            Color::b = u;
        }
        
        float getR();
        float getG();
        float getB();
};

class ModelColor {
    private:
        float diffuse[3], ambient[3], specular[3], emission[3], shininess;

    public:

        ModelColor() {
            // Valores padrão para as cores e brilho
            for (int i = 0; i < 3; ++i) {
                diffuse[i] = 0.5;
                ambient[i] = 0.5;
                specular[i] = 0;
                emission[i] = 0;
            }
            shininess = 0;
        }

        ModelColor(float diffuse[3], float ambient[3], float specular[3], float emission[3], float shininess) {
            for(int i = 0; i < 3; ++i) {
                ModelColor::diffuse[i] = diffuse[i]/255;
                ModelColor::ambient[i] = ambient[i]/255;
                ModelColor::specular[i] = specular[i]/255;
                ModelColor::emission[i] = emission[i]/255;
            }
            ModelColor::shininess = shininess;
        }

        float * getDiffuse();
        float * getAmbient();
        float * getSpecular();
        float * getEmission();
        float getShininess();
};

#endif // COLOURS_HPP
