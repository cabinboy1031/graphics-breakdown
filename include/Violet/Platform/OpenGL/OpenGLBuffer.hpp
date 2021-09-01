#ifndef VIOLET_OPENGL_BUFFER_H_
#define VIOLET_OPENGL_BUFFER_H_
#include "Violet/Renderer/Buffer.hpp"
#include <cstdint>

namespace Violet{
    class OpenGLVertexBuffer: public VertexBuffer{
            public:
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVertexBuffer();

            virtual void bind() const;
            virtual void unbind() const;

            virtual uint32_t getCount() const { return m_Count; }
        private:
            uint32_t
            m_RendererID,
            m_Count;
    };

    class OpenGLIndexBuffer: public IndexBuffer{
            public:
            OpenGLIndexBuffer(uint32_t* vertices, uint32_t size);
            virtual ~OpenGLIndexBuffer();

            virtual void bind() const;
            virtual void unbind() const;

            virtual uint32_t getCount() const { return m_Count; }
        private:
            uint32_t
            m_RendererID,
            m_Count;
    };
}


#endif // VIOLET_OPENGL_BUFFER_H_
