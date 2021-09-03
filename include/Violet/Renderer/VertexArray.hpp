#ifndef VIOLET_VERTEXARRAY_H_
#define VIOLET_VERTEXARRAY_H_
#include "Violet/Renderer/Buffer.hpp"
#include <vector>
#include <cstdint>
#include <memory>

namespace Violet{
    class VertexArray{
        public:
            virtual ~VertexArray(){}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
            virtual void setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) = 0;

            virtual const std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const = 0;
            virtual const std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;

            static VertexArray* create();
    };
}



#endif // VIOLET_VERTEXARRAY_H_
