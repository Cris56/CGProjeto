#include "xmlParser.hpp"

std::string path = "../../data/";

World convertToWorld(const char* fileName) {

    World world;
    
    std::string filePath = path + fileName;

    xml_document doc;
    xml_parse_result result = doc.load_file(filePath.c_str(), parse_default, encoding_auto);
    std::cout << "XML [" << filePath << "] parsed with result [" << result.description() << "]\n";

    // Access the window element
    xml_node window_node = doc.child("world").child("window");
    world.setWidth(window_node.attribute("width").as_int());
    world.setHeight(window_node.attribute("height").as_int());
    
    Camera camera;
    
    // Access the camera position, lookAt, up, and projection elements
    xml_node position_node = doc.child("world").child("camera").child("position");
    camera.setPosition(position_node.attribute("x").as_float(), position_node.attribute("y").as_float(), position_node.attribute("z").as_float());
    
    xml_node lookAt_node = doc.child("world").child("camera").child("lookAt");
    camera.setLookAt(lookAt_node.attribute("x").as_float(), lookAt_node.attribute("y").as_float(), lookAt_node.attribute("z").as_float());

    xml_node up_node = doc.child("world").child("camera").child("up");
    camera.setUp(up_node.attribute("x").as_float(), up_node.attribute("y").as_float(), up_node.attribute("z").as_float());
   
    xml_node projection_node = doc.child("world").child("camera").child("projection");
    camera.setFov(projection_node.attribute("fov").as_float());
    camera.setNear(projection_node.attribute("near").as_float());
    camera.setFar(projection_node.attribute("far").as_float());

    world.setCamera(camera);

    xml_node group_node = doc.child("world").child("group");
    world.setGroup(convertGroup(group_node));
    return world;
}


Group convertGroup(xml_node group_node) {
    Group group;
    xml_node child;

    for (child = group_node.first_child(); child; child = child.next_sibling()) {
        if (std::string(child.name()) == "group") {
            group.addGroup(convertGroup(child));
        } else if (std::string(child.name()) == "transform") {
            Transform transform;

            xml_node transform_node;
            for (transform_node = child.first_child(); transform_node; transform_node = transform_node.next_sibling()) {
                if (std::string(transform_node.name()) == "translate") {
                    float time = transform_node.attribute("time").as_float();
                    float align = transform_node.attribute("align").as_bool();

                    xml_node point_node;
                    for (point_node = transform_node.child("point"); point_node; point_node = point_node.next_sibling("point")) {
                        float x = point_node.attribute("x").as_float();
                        float y = point_node.attribute("y").as_float();
                        float z = point_node.attribute("z").as_float();

                        transform.addTranslationPoint(x, y, z);
                    }
                    transform.setIsAligned(align);
                    transform.setTime(time);
                } else if (std::string(transform_node.name()) == "rotate") {
                    transform.setRotation(transform_node.attribute("time").as_float(), transform_node.attribute("x").as_float(), transform_node.attribute("y").as_float(), transform_node.attribute("z").as_float());
                } else if (std::string(transform_node.name()) == "scale") {
                    transform.setScale(transform_node.attribute("x").as_float(), transform_node.attribute("y").as_float(), transform_node.attribute("z").as_float());
                }
            }

            group.setTransform(transform);
        } else if (std::string(child.name()) == "models") {
            xml_node model_node;
            for (model_node = child.first_child(); model_node; model_node = model_node.next_sibling()) {
                Model model(path, model_node.attribute("file").value());

                // Parsing das cores do modelo
                xml_node color_node = model_node.child("color");
                if (color_node) {
                    float diffuse[3] = {0.5, 0.5, 0.5};
                    float ambient[3] = {0.5, 0.5, 0.5};
                    float specular[3] = {0, 0, 0};
                    float emissive[3] = {0, 0, 0};
                    float shininess = 0;

                    xml_node diffuse_node = color_node.child("diffuse");
                    if (diffuse_node) {
                        float diffuse_r = diffuse_node.attribute("R").as_float();
                        float diffuse_g = diffuse_node.attribute("G").as_float();
                        float diffuse_b = diffuse_node.attribute("B").as_float();
                        diffuse[0] = diffuse_r / 255.0;
                        diffuse[1] = diffuse_g / 255.0;
                        diffuse[2] = diffuse_b / 255.0;
                    }

                    xml_node ambient_node = color_node.child("ambient");
                    if (ambient_node) {
                        float ambient_r = ambient_node.attribute("R").as_float();
                        float ambient_g = ambient_node.attribute("G").as_float();
                        float ambient_b = ambient_node.attribute("B").as_float();
                        ambient[0] = ambient_r / 255.0;
                        ambient[1] = ambient_g / 255.0;
                        ambient[2] = ambient_b / 255.0;
                    }

                    xml_node specular_node = color_node.child("specular");
                    if (specular_node) {
                        float specular_r = specular_node.attribute("R").as_float();
                        float specular_g = specular_node.attribute("G").as_float();
                        float specular_b = specular_node.attribute("B").as_float();
                        specular[0] = specular_r / 255.0;
                        specular[1] = specular_g / 255.0;
                        specular[2] = specular_b / 255.0;
                    }

                    xml_node emissive_node = color_node.child("emissive");
                    if (emissive_node) {
                        float emissive_r = emissive_node.attribute("R").as_float();
                        float emissive_g = emissive_node.attribute("G").as_float();
                        float emissive_b = emissive_node.attribute("B").as_float();
                        emissive[0] = emissive_r / 255.0;
                        emissive[1] = emissive_g / 255.0;
                        emissive[2] = emissive_b / 255.0;
                    }

                    xml_node shininess_node = color_node.child("shininess");
                    if (shininess_node) {
                        float shininess_value = shininess_node.attribute("value").as_float();
                        shininess = shininess_value;
                    }

                    ModelColor model_color(diffuse, ambient, specular, emissive, shininess);
                    model.setColor(model_color);

                    xml_node texture_node = model_node.child("texture");
                    if (texture_node) {
                        std::string texture_file = texture_node.attribute("file").value();
                        model.setTexture(texture_file);
                    }
                }

                 group.addModel(model);
            }
        }

    return group;
}


