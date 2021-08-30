#include <iostream>
#include "Violet.hpp"

#include <chrono>

using namespace std;

class TestLayer: public Violet::Layer {
    public:
        TestLayer()
            : Layer("UPS Timer"){}

        void onUpdate() override {
            auto this_frame_record = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            auto delta = this_frame_record - last_record;
            last_record = this_frame_record;

            glClearColor(0,1,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void onEvent(Violet::Event& event) override {
        }

    private:
        long int last_record;

};

class Sandbox: public Violet::Application {
    public:
        Sandbox(){
            pushLayer(new TestLayer());
            pushOverlay(new Violet::ImguiLayer());
        }

        ~Sandbox(){

        }

};

Violet::Application* Violet::CreateApplication(){
    return new Sandbox();
}
