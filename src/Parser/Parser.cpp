#include "Parser.hpp"
#include "Filesystem/FileManager.hpp"
#include "Debug/Debug.hpp"
#include "Multithread/ThreadManager.hpp"
#include "Multithread/EngineObject.hpp"

#include "Interface/GenericInterface.hpp"
#include "html/base/Body.hpp"
#include "html/base/Root.hpp"

void Parser::Load(string location) {
    if (!FileManager::FileExists(location))
        return Debug::Error("Parser - Failed to find file " + location);

    pugi::xml_parse_result result = doc.load_file(location.c_str(),pugi::parse_default|pugi::parse_declaration);

    if (!result)
        return Debug::Error((string)"Parse error: " + result.description() + ", character pos= " + to_string(result.offset));

    root = doc.document_element();

    if (root.child("Body"))
        loaded = true;
}

void Parser::SpawnNode(VEngine *engine, pugi::xml_node) {

}

void Parser::Instance(VEngine* engine) {
    if (!loaded)
        return;

    //html
    auto* root = new EngineObject();
    auto interface = new GenericInterface();
    interface->style = Style(RootStyle);
    interface->style.color = Vector4(1, 2, 3, 4);
    root->AddComponent(interface);

    ThreadManager::Instance(root, engine);

    //body
    auto* body = new EngineObject();
    interface = new GenericInterface();
    interface->style = Style(BodyStyle);
    body->AddComponent(interface);

    ThreadManager::Instance(body, root);
}