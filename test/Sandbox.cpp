#include <iostream>
#include <chrono>
#include <glm/glm.hpp>

#include <imgui.h>
#include <glad/glad.h>
#include <Violet/Violet.hpp>
#include <Violet/Renderer/Shader.hpp>
#include <Violet/Renderer/Buffer.hpp>
#include <Violet/Renderer/VertexArray.hpp>


using namespace std;
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

class TestLayer: public Violet::Layer {
    public:
        TestLayer()
            : Layer("UPS Timer"){
            // Vertex array
            m_VertexArray.reset(Violet::VertexArray::create());
            float vertices[3 * 7] {
                -0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.6f, 1.0f,
                0.5f, -0.5f, 0.0f,  0.8f, 0.0f, 0.6f, 1.0f,
                0.0f, 0.5f, 0.0f,   0.8f, 0.0f, 0.6f, 1.0f
            };
            m_VertexBuffer.reset(Violet::VertexBuffer::create(vertices,sizeof(vertices)));

            Violet::BufferLayout layout = {
            { Violet::ShaderDataType::Float3, "a_Position" },
            { Violet::ShaderDataType::Float4, "a_Color" }
        };
            VGE_TRACE("stride: {0}", layout.getStride())

            uint32_t index = 0;
            for(const auto& element: layout){
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(index,
                                      element.getComponentCount(),
                                      shaderDataTypeToOpenGLBaseType(element.type),
                                      element.normalized ? GL_TRUE : GL_FALSE,
                                      layout.getStride(),
                                      (const void*)element.offset);
                index++;
            }

            unsigned int indices[3] = {0, 1, 2};
            m_IndexBuffer.reset(Violet::IndexBuffer::create(indices,3));


            std::string vertexSrc = R"(#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
out vec3 v_Position;
out vec4 v_Color;

void main(){
  gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
  v_Position = a_Position;
  v_Color = a_Color;
}
)";

            std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec4 v_Color;

void main(){
  color = v_Color;
}
)";
            m_Shader.reset(Violet::Shader::create(vertexSrc, fragmentSrc));
        }

        void onUpdate() override {
            auto this_frame_record = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            auto delta = this_frame_record - last_record;
            last_record = this_frame_record;

            //VGE_CORE_INFO("{0}", event.toString());
            glClearColor(0,.5f,.5f,1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->bind();
            m_VertexArray->bind();
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);
        }

        void onEvent(Violet::Event& event) override {
            if(Violet::Input::isKeyPressed(Violet::VGE_KEY_TAB)){
                VGE_INFO("Tab key is pressed!");
            }
        }

        void onImguiRender() override{
            ImGui::Begin("test");
            ImGui::Text("Hello world!");
            ImGui::End();
        }

    private:
        long int last_record;
        unsigned int vertexArray, indexBuffer;
        std::unique_ptr<Violet::Shader> m_Shader;
        std::unique_ptr<Violet::VertexArray> m_VertexArray;
        std::unique_ptr<Violet::VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Violet::IndexBuffer> m_IndexBuffer;
        

};

class Sandbox: public Violet::Application {
    public:
        Sandbox(){
            pushLayer(new TestLayer());
        }

        ~Sandbox(){

        }

};

Violet::Application* Violet::CreateApplication(){
    return new Sandbox();
}
