#ifndef __GENERICINTERFACE__
#define __GENERICINTERFACE__

#include "Multithread/Component.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Pipeline.hpp"
#include "Graphics/ShaderData.hpp"
#include "Style/Style.hpp"

const float DEPTH = 1000000;

class GenericInterface : public Component{
private:
    Vector2 position = Vector2();
    Vector2 size = Vector2();
    float z = 1;

    static int indices[6];

    Buffer* vertexBuffer = nullptr;
    Buffer* indiceBuffer = nullptr;
    Shader* shader = nullptr;
    Pipeline* pipeline = nullptr;
    ShaderData* shaderData = nullptr;
public:
    GenericInterface* parent;

    Style style;

    int GetZ();

    void UpdateStyle();

    void UpdateVertex();
    void Load() override;
    void Update() override;
    void PreRender() override;
};

#endif