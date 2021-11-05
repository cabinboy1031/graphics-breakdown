#include <iostream>
#include <chrono>

#include <Violet/Violet.hpp>
#include <Violet/Platform/OpenGL/OpenGLShader.hpp>
#include <imgui.h>

#include <glm/glm.hpp>

using namespace std;
class TestLayer: public Violet::Layer {
    public:
        TestLayer()
            : Layer("UPS Timer"),
              m_Camera(-2.0f, 2.0f, -2.0f, 2.0f)
        {

            // Vertex array
            m_VertexArray.reset(Violet::VertexArray::create());
            Violet::Reference<Violet::VertexBuffer> m_VertexBuffer;
            Violet::Reference<Violet::IndexBuffer> m_IndexBuffer;

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
            Violet::Reference<Violet::VertexBuffer> squareVB;
            Violet::Reference<Violet::IndexBuffer> squareIB;

            float squareVertices[5 * 4] {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

            };

            squareVB.reset(Violet::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
            squareVB->setLayout({
                {Violet::ShaderDataType::Float3, "a_Position"},
                {Violet::ShaderDataType::Float2, "a_TexCoord"}
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

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main(){
  gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
  v_Position = a_Position;
  v_Color = a_Color;
}
)";

            std::string fragmentSrc = R"(#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec4 v_Color;

uniform vec4 u_Color;

void main(){
  color = u_Color;
}
)";

            m_FlatColorShader.reset(Violet::Shader::create(vertexSrc, fragmentSrc));
            std::string vertexSrc2 = R"(#version 330 core

layout(location = 0) in vec3 a_Position;
out vec3 v_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main(){
  gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

            std::string vertexSrc3 = R"(#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec3 v_Position;
out vec2 v_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main(){
  v_TexCoord = a_TexCoord;
  gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
)";

            std::string fragmentSrc3 = R"(#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

uniform vec4 u_Color;

void main(){
  color = texture(u_Texture, v_TexCoord);
}
)";

            m_TextureShader.reset(Violet::Shader::create(vertexSrc3, fragmentSrc3));
            std::dynamic_pointer_cast<Violet::OpenGLShader>(m_TextureShader)->uploadUniformInt("u_Texture", 0);
            m_TextureShader->bind();

            m_CheckerboardTex = Violet::Texture2D::create("./build/bin/assets/textures/pattern.png");
            m_TransparentTex = Violet::Texture2D::create("./build/bin/assets/textures/transparent.png");

        }

        void onUpdate(Violet::Timestep deltaTime) override {
            //VGE_CORE_INFO("Delta time: {0}({1} UPS)", deltaTime.getSeconds(), 1.0/deltaTime.getSeconds());
            Violet::RenderCommand::setClearColor({0,.5f,.5f,1});
            Violet::RenderCommand::clear();
            //float newRotation = m_Camera.getRotation();
            //newRotation =  newRotation + 0.5f;
            //m_Camera.setRotation(newRotation);

            if(Violet::Input::isKeyPressed(Violet::VGE_KEY_W)){
                 m_CameraPosition.y += m_CameraSpeed * deltaTime.getSeconds();
            }
            if(Violet::Input::isKeyPressed(Violet::VGE_KEY_S)){
                m_CameraPosition.y -= m_CameraSpeed * deltaTime.getSeconds();
            }
            if(Violet::Input::isKeyPressed(Violet::VGE_KEY_A)){
                m_CameraPosition.x -= m_CameraSpeed * deltaTime.getSeconds();
            }
            if(Violet::Input::isKeyPressed(Violet::VGE_KEY_D)){
                m_CameraPosition.x += m_CameraSpeed * deltaTime.getSeconds();
            }

            //m_Camera.setPosition(m_CameraPosition);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

            Violet::Renderer::beginScene(m_Camera);
            m_FlatColorShader->bind();
            for (int i = -10; i <= 10; i++){
                for(int j = -10; j <= 10; j++){
                    if((i + j) % 2 == 0){
                        std::dynamic_pointer_cast<Violet::OpenGLShader>(m_FlatColorShader)->uploadUniformFloat4("u_Color", m_RedColor);
                    } else {
                        std::dynamic_pointer_cast<Violet::OpenGLShader>(m_FlatColorShader)->uploadUniformFloat4("u_Color", m_BlueColor);
                    }
                    glm::vec3 pos(i * 0.11f, j * 0.11f ,0.0f);
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                    Violet::Renderer::submit(m_FlatColorShader,m_SquareVA,transform);
                }
            }
            std::dynamic_pointer_cast<Violet::OpenGLShader>(m_FlatColorShader)->uploadUniformFloat4("u_Color", {0.8f, 0.0f, 0.6f, 1.0f});
            Violet::Renderer::submit(m_Shader2,m_SquareVA, glm::translate(glm::mat4(1.0), m_CameraPosition));
            Violet::Renderer::submit(m_FlatColorShader, m_VertexArray);


            m_CheckerboardTex->bind(0);
            Violet::Renderer::submit(m_TextureShader, m_SquareVA,
                                    glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
            m_TransparentTex->bind(0);
            Violet::Renderer::submit(m_TextureShader, m_SquareVA,
                                    glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

            Violet::Renderer::endScene();
        }

        void onEvent(Violet::Event& event) override {
            Violet::EventDispatcher dispatcher(event);
            dispatcher.dispatch<Violet::KeyPressedEvent>(VGE_BIND_EVENT_FN(TestLayer::onKeyPressed));
        }

        bool onKeyPressed(Violet::KeyPressedEvent& event){

            return true;
        }

        void onImguiRender(Violet::Timestep deltaTime) override{
            ImGui::Begin("Settings");
            ImGui::ColorEdit4("Red Color", glm::value_ptr(m_RedColor));
            ImGui::ColorEdit4("Blue Color", glm::value_ptr(m_BlueColor));
            ImGui::End();
        }

    private:
        Violet::Reference<Violet::Shader> m_FlatColorShader, m_TextureShader;
        Violet::Reference<Violet::Shader> m_Shader2;
        Violet::Reference<Violet::VertexArray> m_VertexArray;
        Violet::Reference<Violet::VertexArray> m_SquareVA;
        Violet::Reference<Violet::Texture2D> m_CheckerboardTex;
        Violet::Reference<Violet::Texture2D> m_TransparentTex;

        Violet::OrthographicCamera m_Camera;

        glm::vec4 m_RedColor = {176.0f / 255.0f, 53.0f / 255.f, 42.f / 255.f, 1.0f};
        glm::vec4 m_BlueColor = {42.0f / 255.0f, 53.0f / 255.f, 176.f / 255.f, 1.0f};

        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraSpeed = 1.f;

};

class Sandbox: public Violet::Application {
    public:
        Sandbox(){
            pushLayer(new TestLayer());
        }

        ~Sandbox(){
            VGE_TRACE("Beginning cleanup.")
        }

};

Violet::Application* Violet::CreateApplication(){
    return new Sandbox();
}
