#include "Violet/Platform/OpenGL/OpenGLVertexArray.hpp"
#include "glad/glad.h"

using namespace Violet;

OpenGLVertexArray::OpenGLVertexArray(){
    glGenVertexArrays(1,&m_RendererID);
    bind();
}

OpenGLVertexArray::~OpenGLVertexArray(){
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::bind() const {
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::unbind() const {
    glBindVertexArray(0);

}
