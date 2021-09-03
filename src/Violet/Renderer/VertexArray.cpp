#include "Violet/Log.hpp"
#include "Violet/Renderer/Renderer.hpp"
#include "Violet/Renderer/VertexArray.hpp"
#include "Violet/Platform/OpenGL/OpenGLVertexArray.hpp"
using namespace Violet;

VertexArray* VertexArray::create(){
    switch(RendererAPI::getAPI()){
        case(RendererAPI::API::OpenGL):       return new OpenGLVertexArray();
        case(RendererAPI::API::None):         VGE_CORE_ASSERT(false, "RendererAPI::None currently returns nullptr.");
    }
    return nullptr;

}
