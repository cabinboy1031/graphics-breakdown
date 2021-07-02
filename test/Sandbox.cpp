#include <iostream>
#include "Violet.hpp"

using namespace std;

class ExampleLayer: public Violet::Layer {
    public:
        ExampleLayer()
            : Layer("Example"){}

        void onUpdate() override {
            VGE_INFO("ExampleLayer::Update");
        }

        void onEvent(Violet::Event& event) override {
            VGE_TRACE("{0}", event.toString());
        }
};

class Sandbox: public Violet::Application {
    public:
        Sandbox(){
            pushLayer(new ExampleLayer());
        }

        ~Sandbox(){

        }

};

Violet::Application* Violet::CreateApplication(){
    return new Sandbox();
}
