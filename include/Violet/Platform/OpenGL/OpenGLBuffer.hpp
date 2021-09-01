#ifndef VIOLET_OPENGL_BUFFER_H_
#define VIOLET_OPENGL_BUFFER_H_
#include "Violet/Renderer/Buffer.hpp"
#include <cstdint>
#include <glad/glad.h>

namespace Violet{

    class OpenGLVertexBuffer: public VertexBuffer{
            public:
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVertexBuffer() override;

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual const BufferLayout& getLayout() const override { return m_Layout; }
            virtual void setLayout(const BufferLayout& layout) override { m_Layout = layout; }

            virtual uint32_t getCount() const override { return m_Count; }
        private:
            uint32_t
            m_RendererID,
            m_Count;
            BufferLayout m_Layout;
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
