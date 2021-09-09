#ifndef VIOLET_RENDERER_API_H
#define VIOLET_RENDERER_API_H

#include <glm/glm.hpp>
#include <memory>

#include "VertexArray.hpp"

namespace Violet{
    class RendererAPI{
        public:
            enum class API {
            None = 0,
            OpenGL = 1
        };
        public:
            virtual void setClearColor(glm::vec4 color) = 0;
            virtual void clear() = 0;

            virtual void drawIndexed(const Reference<VertexArray> vertexArray) = 0;

            inline static API getAPI() { return s_API; }
        private:
            static API s_API;

    };
}

#endif // VIOLET_RENDERERAPI_H
