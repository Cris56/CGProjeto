#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "World.hpp"
#include "pugixml.hpp"

using namespace pugi;

World convertToWorld(const char* fileName);
Group convertGroup(pugi::xml_node group_node);

#endif // XMLPARSER_HPP
