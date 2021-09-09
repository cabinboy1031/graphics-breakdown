#include "Violet/Renderer/Renderer.hpp"
#include "Violet/Platform/OpenGL/OpenGLShader.hpp"

using namespace Violet;
glm::mat4 Renderer::s_ViewProjectionMatrix = glm::mat4(0.0f);
void Renderer::beginScene(Camera& camera){
    s_ViewProjectionMatrix = camera.getViewProjectionMatrix();
}

void Renderer::endScene(){}

void Renderer::submit(const Reference<Shader>& shader,
                      const Reference<VertexArray>& vertexArray,
                      const glm::mat4& transform){
    shader->bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_Transform", transform);

    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}
