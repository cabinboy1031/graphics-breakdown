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

            virtual void addVertexBuffer(Reference<VertexBuffer> vertexBuffer) = 0;
            virtual void setIndexBuffer(Reference<IndexBuffer> indexBuffer) = 0;

            virtual const std::vector<Reference<VertexBuffer>> getVertexBuffers() const = 0;
            virtual const Reference<IndexBuffer> getIndexBuffer() const = 0;

            static VertexArray* create();
    };
}



#endif // VIOLET_VERTEXARRAY_H_
