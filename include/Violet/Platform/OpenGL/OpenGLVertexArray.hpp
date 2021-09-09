#ifndef VIOLET_OPENGL_VERTEXARRAY_H_
#define VIOLET_OPENGL_VERTEXARRAY_H_
#include "Violet/Renderer/Buffer.hpp"
#include "Violet/Renderer/VertexArray.hpp"

namespace Violet{
    class OpenGLVertexArray: public VertexArray {
        public:
            OpenGLVertexArray();
            virtual ~OpenGLVertexArray();

            virtual void bind() const override;
            virtual void unbind() const override;

            virtual void addVertexBuffer(Reference<VertexBuffer> vertexBuffer) override;
            virtual void setIndexBuffer(Reference<IndexBuffer> indexBuffer) override;

            virtual const std::vector<Reference<VertexBuffer>> getVertexBuffers() const override
            { return m_VertexBuffers; }
            virtual const Reference<IndexBuffer> getIndexBuffer() const override
            { return m_IndexBuffer; }
        private:
            uint32_t m_RendererID;
            std::vector<Reference<VertexBuffer>> m_VertexBuffers;
            Reference<IndexBuffer> m_IndexBuffer;

    };
}


#endif // VIOLET_OPENGL_VERTEXARRAY_H_
