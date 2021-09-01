#include "Violet/Renderer/Shader.hpp"
#include "Violet/Platform/OpenGL/OpenGLShader.hpp"
#include "Violet/Renderer/Renderer.hpp"

using namespace Violet;

Shader* Shader::create(const std::string vertexSrc,
                       const std::string fragmentSrc){
    switch(Renderer::getAPI()){
        case(RendererAPI::OpenGL):       return new OpenGLShader(vertexSrc, fragmentSrc);
        case(RendererAPI::None):         VGE_CORE_ASSERT(false, "RendererAPI::None currently returns nullptr.");
    }
    return nullptr;
}
