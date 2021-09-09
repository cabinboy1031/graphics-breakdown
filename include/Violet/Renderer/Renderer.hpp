#ifndef VIOLET_RENDERER_H
#define VIOLET_RENDERER_H

#include "RendererAPI.hpp"
#include "RenderCommand.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

namespace Violet{
    class Renderer{
        public:
            static void beginScene(Camera& camera);
            static void endScene();

            static void submit(const Reference<Shader>& shader,
                               const Reference<VertexArray>& vertexArray,
                               const glm::mat4& transform = glm::mat4(1.0f));
            inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

        private:
            static glm::mat4 s_ViewProjectionMatrix;
    };
}


#endif // VIOLET_RENDERER_API_H
