#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "world.hpp"
#include "pugixml.hpp"
#include <iostream>

using namespace pugi;

World convertToWorld(const char* fileName);
Group convertGroup(pugi::xml_node group_node);

#endif // XMLPARSER_HPP
