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

            virtual void addVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
            virtual void setIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) override;

            virtual const std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const override
            { return m_VertexBuffers; }
            virtual const std::shared_ptr<IndexBuffer> getIndexexBuffer() const override
            { return m_IndexBuffer; }
        private:
            uint32_t m_RendererID;
            std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;

    };
}


#endif // VIOLET_OPENGL_VERTEXARRAY_H_
