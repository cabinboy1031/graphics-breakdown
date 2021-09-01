#include "Violet/Platform/OpenGL/OpenGLBuffer.hpp"
#include <glad/glad.h>

using namespace Violet;

//////////////////////////////////////////////////////////////////////
// Vertex Buffer
//////////////////////////////////////////////////////////////////////

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t count)
    :m_Count(count){
    glGenBuffers(1, &m_RendererID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float) , vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer(){
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
void OpenGLVertexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//////////////////////////////////////////////////////////////////////
// Index Buffer
//////////////////////////////////////////////////////////////////////

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    :m_Count(count){
    glGenBuffers(1, &m_RendererID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer(){
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}
void OpenGLIndexBuffer::unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//////////////////////////////////////////////////////////////////////
