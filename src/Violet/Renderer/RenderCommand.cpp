#include "Violet/Renderer/RenderCommand.hpp"
#include "Violet/Platform/OpenGL/OpenGLRenderAPI.hpp"

namespace Violet{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
