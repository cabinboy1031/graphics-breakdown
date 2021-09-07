#include "Violet/Renderer/Renderer.hpp"

using namespace Violet;
glm::mat4 Renderer::s_ViewProjectionMatrix = glm::mat4(0.0f);
void Renderer::beginScene(Camera& camera){
    s_ViewProjectionMatrix = camera.getViewProjectionMatrix();
}

void Renderer::endScene(){}

void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray){
    shader->bind();
    shader->uploadUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);

    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}
