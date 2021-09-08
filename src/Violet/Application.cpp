#include "Violet/Application.hpp"

#include "Violet/Events/ApplicationEvent.hpp"
#include "Violet/Log.hpp"

#include <glm/glm.hpp>

// Temporary
#include "GLFW/glfw3.h"
using namespace Violet;

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application(){
    VGE_CORE_ASSERT(!s_Instance, "Application already exists!");

    m_Window = std::unique_ptr<Window>(Window::create(WindowProps("Main window", 800, 800)));
    m_Window->setEventCallback(BIND_EVENT_FN(onEvent));

    s_Instance = this;

    m_ImguiLayer = new ImguiLayer();
    pushOverlay(m_ImguiLayer);
}

Application::~Application(){

}

void Application::run(){
    while (m_Running){
        float time = (float)glfwGetTime();
        Timestep deltaTime = time - m_LastFrameTime;
        m_LastFrameTime = time;

        for(Layer* layer: m_LayerStack)
            layer->onUpdate(deltaTime);

        m_ImguiLayer->begin();
        for(Layer* layer: m_LayerStack){
            layer->onImguiRender(deltaTime);
        }
        m_ImguiLayer->end();

        m_Window->onUpdate();
    }
}

void Application::onEvent(Event& e){
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));


    for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ){
        (*--it)->onEvent(e);
        if(e.handled())
            break;
    }
}

bool Application::onWindowClose(WindowCloseEvent& e){
    m_Running = false;
    return true;
}

void Application::pushLayer(Layer* layer){
    m_LayerStack.pushLayer(layer);
}

void Application::pushOverlay(Layer* overlay){
    m_LayerStack.pushOverlay(overlay);
}
