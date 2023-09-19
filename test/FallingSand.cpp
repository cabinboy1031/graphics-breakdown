#include <iostream>
#include <chrono>

#include <Violet/Violet.hpp>
#include <Violet/Platform/OpenGL/OpenGLShader.hpp>
#include <imgui.h>

#include <glm/glm.hpp>

using namespace std;

class FallingSandLayer: public Violet::Layer {
    public:
        FallingSandLayer()
            :Layer("Falling Sand"),
             m_camera(-1.0f,1.0f,-1.0f, 1.0f)
        {
            VGE_TRACE("Initializing FallingSand layer.");
            m_screenSizeArray.reset(Violet::VertexArray::create());
            Violet::Reference<Violet::VertexBuffer> m_screenSizeVertexBuffer;
            Violet::Reference<Violet::IndexBuffer> m_IndexBuffer;

            // We are rendering everything to an image texture, so position should be all we need...?
            Violet::BufferLayout layout = {
            {Violet::ShaderDataType::Float3, "a_Position"},
            {Violet::ShaderDataType::Float2, "a_TexCoord"}};

            float vertices[5*4] {
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            };
            m_screenSizeVertexBuffer.reset(Violet::VertexBuffer::create(vertices, sizeof(vertices)));

            m_screenSizeVertexBuffer->setLayout(layout);
            m_screenSizeArray->addVertexBuffer(m_screenSizeVertexBuffer);

            unsigned int indices[6] = {
            0, 1, 2,
            2, 3,0
        };
            m_IndexBuffer.reset(Violet::IndexBuffer::create(indices, 6));
            m_screenSizeArray->setIndexBuffer(m_IndexBuffer);

            m_fallingSandShader.reset(Violet::Shader::create("./assets/shaders/sand_world.glsl"));
            m_fallingSandWorldTexture.reset(Violet::Texture2D::create(const std::string &path));


        }

        void onUpdate(Violet::Timestep deltaTime) override {

            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
            Violet::Renderer::beginScene(m_camera);{
                m_fallingSandWorldTexture->bind(0);

                m_fallingSandShader->bind();
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3({0,0,0})) * scale;
                Violet::Renderer::submit(m_fallingSandShader, m_screenSizeArray,transform);

            } Violet::Renderer::endScene();
        }

        void onEvent(Violet::Event& event) override {
            Violet::EventDispatcher dispatcher(event);
            dispatcher.dispatch<Violet::KeyPressedEvent>(VGE_BIND_EVENT_FN(FallingSandLayer::onKeyPressed));
        }

        bool onKeyPressed(Violet::KeyPressedEvent& event){

            return true;
        }

        void onImguiRender(Violet::Timestep deltaTime) override {

        };



    private:
        Violet::Reference<Violet::Shader> m_fallingSandShader;
        Violet::Reference<Violet::Texture2D> m_fallingSandWorldTexture;
        Violet::Reference<Violet::VertexArray> m_screenSizeArray;
        Violet::Reference<Violet::BufferLayout> m_screenSizeBufferLayout;

        Violet::OrthographicCamera m_camera;
};

class FallingSandGame: public Violet::Application {
    public:
        FallingSandGame(){
            pushLayer(new FallingSandLayer());
        }

        ~FallingSandGame(){
            VGE_TRACE("Beginning cleanup.")
        }
};

Violet::Application* Violet::CreateApplication(){
    return new FallingSandGame();
}
