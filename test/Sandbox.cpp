#include <iostream>
#include <chrono>
#include <glm/glm.hpp>

#include <imgui.h>
#include <glad/glad.h>
#include <Violet/Violet.hpp>


using namespace std;

class TestLayer: public Violet::Layer {
    public:
        TestLayer()
            : Layer("UPS Timer"){}

        void onUpdate() override {
            auto this_frame_record = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            auto delta = this_frame_record - last_record;
            last_record = this_frame_record;

            //VGE_CORE_INFO("{0}", event.toString());
            glClearColor(1,0,0,1);
            glClear(GL_COLOR_BUFFER_BIT);
             
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
