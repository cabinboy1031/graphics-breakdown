#ifndef VIOLET_RENDERER_H
#define VIOLET_RENDERER_H

#include "RendererAPI.hpp"
#include "RenderCommand.hpp"
#include "VertexArray.hpp"

namespace Violet{
    class Renderer{
        public:
            static void beginScene();
            static void endScene();

            static void submit(const std::shared_ptr<VertexArray>& vertexArray);
            inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
    };
}


#endif // VIOLET_RENDERER_API_H
