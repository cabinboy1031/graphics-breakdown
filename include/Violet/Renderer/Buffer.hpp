#ifndef VIOLET_BUFFER_H
#define VIOLET_BUFFER_H
#include "Violet/Renderer/Renderer.hpp"
#include <cstdint>

namespace Violet{
    class VertexBuffer {
        public:
            virtual ~VertexBuffer() {}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual uint32_t getCount() const = 0;

            static VertexBuffer* create(float* vertices, uint32_t size);
    };

    class IndexBuffer {
        public:
            virtual ~IndexBuffer() {}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual uint32_t getCount() const = 0;

            static IndexBuffer* create(uint32_t* vertices, uint32_t size);
    };
}


#endif // VIOLET_BUFFER_H
