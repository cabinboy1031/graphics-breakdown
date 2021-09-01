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
class TestLayer: public Violet::Layer {
    public:
        TestLayer()
            : Layer("UPS Timer"){
            // Vertex array
            m_VertexArray.reset(Violet::VertexArray::create());
            std::shared_ptr<Violet::VertexBuffer> m_VertexBuffer;
            std::shared_ptr<Violet::IndexBuffer> m_IndexBuffer;

            //Vertex layout
            Violet::BufferLayout layout = {
            { Violet::ShaderDataType::Float3, "a_Position" },
            { Violet::ShaderDataType::Float4, "a_Color" }};
            //Vertex data
            float vertices[3 * 7] {
                -0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.6f, 1.0f,
                0.5f, -0.5f, 0.0f,  0.8f, 0.0f, 0.6f, 1.0f,
                0.0f, 0.5f, 0.0f,   0.8f, 0.0f, 0.6f, 1.0f
            };
            m_VertexBuffer.reset(Violet::VertexBuffer::create(vertices,sizeof(vertices)));

            m_VertexBuffer->setLayout(layout);
            m_VertexArray->addVertexBuffer(m_VertexBuffer);

            unsigned int indices[3] = {0, 1, 2};
            m_IndexBuffer.reset(Violet::IndexBuffer::create(indices,3));
            m_VertexArray->setIndexBuffer(m_IndexBuffer);

            m_SquareVA.reset(Violet::VertexArray::create());
            std::shared_ptr<Violet::VertexBuffer> squareVB;
            std::shared_ptr<Violet::IndexBuffer> squareIB;

            float squareVertices[3 * 4] {
                -0.75f, -0.75f, 0.0f,
                 0.75f, -0.75f, 0.0f,
                 0.75f,  0.75f, 0.0f,
                -0.75f,  0.75f, 0.0f,
            };

            squareVB.reset(Violet::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
            squareVB->setLayout({
                {Violet::ShaderDataType::Float3, "a_Position"}
            });

            m_SquareVA->addVertexBuffer(squareVB);
            unsigned int squareIndices[6] = {
            0, 1, 2,
            2, 3, 0
        };
            squareIB.reset(Violet::IndexBuffer::create(squareIndices,6));
            m_SquareVA->setIndexBuffer(squareIB);

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

            std::string fragmentSrc = R"(#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec4 v_Color;

void main(){
  color = v_Color;
}
)";

            m_Shader.reset(Violet::Shader::create(vertexSrc, fragmentSrc));
            std::string vertexSrc2 = R"(#version 330 core

layout(location = 0) in vec3 a_Position;
out vec3 v_Position;

void main(){
  gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
  v_Position = a_Position;
}
)";

            std::string fragmentSrc2 = R"(#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;

void main(){
  color = vec4(v_Position * 0.5 + 0.5, 1.0);
}
)";
            m_Shader2.reset(Violet::Shader::create(vertexSrc2, fragmentSrc2));

        }

        void onUpdate() override {
            //VGE_CORE_INFO("{0}", event.toString());
            glClearColor(0,.5f,.5f,1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader2->bind();
            m_SquareVA->bind();
            glDrawElements(GL_TRIANGLES, m_SquareVA->getIndexexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

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
        std::shared_ptr<Violet::Shader> m_Shader;
        std::shared_ptr<Violet::Shader> m_Shader2;
        std::shared_ptr<Violet::VertexArray> m_VertexArray;
        std::shared_ptr<Violet::VertexArray> m_SquareVA;
        

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
