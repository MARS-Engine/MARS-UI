#ifndef __PARSER__
#define __PARSER__

#include <string>
#include <pugixml.hpp>

using namespace std;

class VEngine;

class Parser {
private:
    pugi::xml_document doc;
    pugi::xml_node root;
    bool loaded = false;

    void SpawnNode(VEngine* engine, pugi::xml_node);
public:

    void Load(string location);
    void Instance(VEngine* engine);
};

#endif