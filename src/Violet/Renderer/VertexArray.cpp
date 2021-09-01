#include "Violet/Log.hpp"
#include "Violet/Renderer/Renderer.hpp"
#include "Violet/Renderer/VertexArray.hpp"
#include "Violet/Platform/OpenGL/OpenGLVertexArray.hpp"
using namespace Violet;

VertexArray* VertexArray::create(){
    switch(Renderer::getAPI()){
        case(RendererAPI::OpenGL):       return new OpenGLVertexArray();
        case(RendererAPI::None):         VGE_CORE_ASSERT(false, "RendererAPI::None currently returns nullptr.");
    }
    return nullptr;

}
