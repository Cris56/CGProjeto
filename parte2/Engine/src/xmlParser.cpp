#include "XMLParser.hpp"
#include <iostream>

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

            for(xml_node transform_node = child.first_child(); transform_node; transform_node = transform_node.next_sibling()) {
                if (std::string(transform_node.name()) == "translate") {
                    transform.setTranslation(transform_node.attribute("x").as_float(), transform_node.attribute("y").as_float(), transform_node.attribute("z").as_float());
                } else if (std::string(transform_node.name()) == "rotate") {
                    transform.setRotation(transform_node.attribute("x").as_float(), transform_node.attribute("y").as_float(), transform_node.attribute("z").as_float(), transform_node.attribute("angle").as_float());
                } else if (std::string(transform_node.name()) == "scale") {
                    transform.setScale(transform_node.attribute("x").as_float(), transform_node.attribute("y").as_float(), transform_node.attribute("z").as_float());
                }
            }
            group.setTransform(transform);

        } else if (std::string(child.name()) == "models") {
            xml_node model_node;
            for (model_node = child.first_child(); model_node; model_node = model_node.next_sibling()) {
                Model model(path, model_node.attribute("file").value());
                group.addModel(model);
            }
        }
    }

    return group;
}
