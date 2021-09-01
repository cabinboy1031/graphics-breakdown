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
            float vertices[3 * 3] {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f,
            };
            m_VertexBuffer.reset(Violet::VertexBuffer::create(vertices,sizeof(vertices)));

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

            unsigned int indices[3] = {0, 1, 2};
            m_IndexBuffer.reset(Violet::IndexBuffer::create(indices,3));


            std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;
out vec3 v_Position;

void main(){
  gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
  v_Position = a_Position;
}
)";

            std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;

void main(){
  color = vec4((v_Position * 0.5 + 0.5), 1.0);
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
            // Shader
             
            // glm::vec3 vector(10, 14, 10);
            // VGE_INFO("{0}, {1}, {2}", vector.x, vector.y, vector.z)
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
