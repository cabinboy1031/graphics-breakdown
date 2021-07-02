#include <iostream>
#include "Violet.hpp"

#include <chrono>

using namespace std;

class FrameTimerLayer: public Violet::Layer {
    public:
        FrameTimerLayer()
            : Layer("UPS Timer"){}

        void onUpdate() override {
            auto this_frame_record = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            auto delta = this_frame_record - last_record;
            VGE_INFO("FrameTimerLayer::Update: {0}ms", delta);
            last_record = this_frame_record;
        }

        void onEvent(Violet::Event& event) override {
            VGE_TRACE("{0}", event.toString());
        }

    private:
        long int last_record;

};

class Sandbox: public Violet::Application {
    public:
        Sandbox(){
            pushLayer(new FrameTimerLayer());
        }

        ~Sandbox(){

        }

};

Violet::Application* Violet::CreateApplication(){
    return new Sandbox();
}
