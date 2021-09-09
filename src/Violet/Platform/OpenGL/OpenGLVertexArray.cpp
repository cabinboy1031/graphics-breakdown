#include "Violet/Platform/OpenGL/OpenGLVertexArray.hpp"
#include "Violet/Platform/OpenGL/OpenGLBuffer.hpp"
#include "glad/glad.h"
#include <memory>

using namespace Violet;
static GLenum shaderDataTypeToOpenGLBaseType(Violet::ShaderDataType type){
    switch(type){
        case(Violet::ShaderDataType::Float):  return GL_FLOAT;
        case(Violet::ShaderDataType::Float2): return GL_FLOAT;
        case(Violet::ShaderDataType::Float3): return GL_FLOAT;
        case(Violet::ShaderDataType::Float4): return GL_FLOAT;
        case(Violet::ShaderDataType::Mat3):   return GL_FLOAT;
        case(Violet::ShaderDataType::Mat4):   return GL_FLOAT;
        case(Violet::ShaderDataType::Int):    return GL_INT;
        case(Violet::ShaderDataType::Int2):   return GL_INT;
        case(Violet::ShaderDataType::Int3):   return GL_INT;
        case(Violet::ShaderDataType::Int4):   return GL_INT;
        case(Violet::ShaderDataType::Bool):   return GL_BOOL;
        default:
            break;
    };
    VGE_CORE_ASSERT(false, "Unknown data type!")
        return 0;
}


OpenGLVertexArray::OpenGLVertexArray(){
    glGenVertexArrays(1,&m_RendererID);
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

void OpenGLVertexArray::addVertexBuffer(Reference<VertexBuffer> vertexBuffer){

    glBindVertexArray(m_RendererID);
    vertexBuffer->bind();
    VGE_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex buffer has no layout!");

    uint32_t index = 0;
    for(const auto& element: vertexBuffer->getLayout()){
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.getComponentCount(),
                              shaderDataTypeToOpenGLBaseType(element.type),
                              element.normalized ? GL_TRUE : GL_FALSE,
                              vertexBuffer->getLayout().getStride(),
                              (const void*)element.offset);
        index++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(Reference<IndexBuffer> indexBuffer){
    glBindVertexArray(m_RendererID);
    indexBuffer->bind();

    m_IndexBuffer = indexBuffer;
}
