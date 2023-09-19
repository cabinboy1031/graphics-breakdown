#include "Violet/Renderer/Texture.hpp"

#include "Violet/Renderer/Renderer.hpp"
#include "Violet/Platform/OpenGL/OpenGLTexture.hpp"

using namespace Violet;

Reference<Texture2D> Texture2D::create(const std::string &path){
    switch(RendererAPI::getAPI()){
        case(RendererAPI::API::OpenGL):       return std::make_shared<OpenGLTexture2D>(path);
        case(RendererAPI::API::None):         VGE_CORE_ASSERT(false, "RendererAPI::None currently returns nullptr.");
    }
    return nullptr;
}

Reference<Texture2D> Texture2D::create(const TextureSpecification& specification){
    switch(RendererAPI::getAPI()){
        case(RendererAPI::API::OpenGL):       return std::make_shared<OpenGLTexture2D>(specification);
        case(RendererAPI::API::None):         VGE_CORE_ASSERT(false, "RendererAPI::None currently returns nullptr.");
    }
    return nullptr;
}
