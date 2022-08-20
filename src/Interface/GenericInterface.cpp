#include "GenericInterface.hpp"
#include "Manager/ShaderManager.hpp"
#include "Manager/PipelineManager.hpp"
#include "Components/Graphics/Camera.hpp"

int GenericInterface::indices[6] = { 0, 1, 2, 1, 3, 2 };

void GenericInterface::UpdateVertex() {
    float depth = GetZ();

    Vector3 Verticies[4] {
        {position.x         , position.y         , DEPTH - min(DEPTH, max(depth, 1.f))},
        {position.x + size.x, position.y         , DEPTH - min(DEPTH, max(depth, 1.f))},
        {position.x         , position.y + size.y, DEPTH - min(DEPTH, max(depth, 1.f))},
        {position.x + size.x, position.y + size.y, DEPTH - min(DEPTH, max(depth, 1.f))}
    };

    vertexBuffer->Update(Verticies);
}

int GenericInterface::GetZ() {
    return style.z + (parent ? parent->GetZ() : 0);
}

void GenericInterface::UpdateStyle() {
    Vector2 pSize = Vector2();
    Vector2 pPos = Vector2();
    Window* window = GetEngine()->window;

    if (parent) {
        pSize  = parent->size;
        pPos = parent->position;
    }

    size = style.GetSize(pSize, window);
    position = style.GetPosition(pPos);

    UpdateVertex();
}

void GenericInterface::Load() {
    isRenderer = true;

    vertexBuffer = new Buffer(GetEngine());
    vertexBuffer->Create(sizeof(Vector3) * 4, MEM_BUFF_VERTEX);

    indiceBuffer = new Buffer(GetEngine());
    indiceBuffer->Create(sizeof(uint32_t) * 6, MEM_BUFF_INDEX);
    indiceBuffer->Update(&indices);

    shader = ShaderManager::GetShader("Engine/Assets/Shaders/Interface.shader", GetEngine());

    pipeline = PipelineManager::GetPipeline("SpritePipeline");

    if (pipeline == nullptr) {
        auto desc = Vector3::GetDescription();
        pipeline = new Pipeline(GetEngine(), shader);
        pipeline->CreateLayout();
        pipeline->ApplyInputDescription(&desc);
        pipeline->Create();
        PipelineManager::AddPipeline("SpritePipeline", pipeline);
    }

    shaderData = new ShaderData(shader, GetEngine());
    shaderData->GetUniform("ORTHO")->Generate(sizeof(Matrix4));
    shaderData->GetUniform("COLOR")->Generate(sizeof(Vector4));
    shaderData->Generate();

    shaderData->GetUniform("ORTHO")->Update(&GetEngine()->GetCamera()->Ortho);

    if (object->parent)
        parent = object->parent->GetComponent<GenericInterface>();

    UpdateStyle();
}

void GenericInterface::PreRender() {
    pipeline->Bind(GetCommandBuffer());
    vertexBuffer->Bind(GetCommandBuffer());
    indiceBuffer->Bind(GetCommandBuffer());
    shaderData->Bind(GetCommandBuffer(), pipeline);
    GetCommandBuffer()->DrawIndexed(6, 1);
}

void GenericInterface::Update() {
     shaderData->GetUniform("COLOR")->Update(&style.background_color);
}