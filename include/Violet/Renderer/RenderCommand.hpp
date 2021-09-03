#ifndef VIOLET_RENDERCOMMAND_H_
#define VIOLET_RENDERCOMMAND_H_

#include "RendererAPI.hpp"

namespace Violet{
    class RenderCommand {
        public:
            inline static void setClearColor(const glm::vec4 color){
                s_RendererAPI->setClearColor(color);
            }

            inline static void clear(){
                s_RendererAPI->clear();
            }

            inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray){
                s_RendererAPI->drawIndexed(vertexArray);
            }
        private:
            static RendererAPI* s_RendererAPI;
    };
}


#endif // VIOLET_RENDERCOMMAND_H_
