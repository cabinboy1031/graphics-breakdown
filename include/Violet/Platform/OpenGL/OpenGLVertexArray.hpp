#ifndef VIOLET_OPENGL_VERTEXARRAY_H_
#define VIOLET_OPENGL_VERTEXARRAY_H_
#include "Violet/Renderer/VertexArray.hpp"

namespace Violet{
    class OpenGLVertexArray: public VertexArray {
        public:
            OpenGLVertexArray();
            virtual ~OpenGLVertexArray();

            virtual void bind() const;
            virtual void unbind() const;
        private:
            uint32_t m_RendererID;
    };
}


#endif // VIOLET_OPENGL_VERTEXARRAY_H_
