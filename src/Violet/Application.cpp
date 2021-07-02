#include "Application.hpp"

#include "Violet/Events/ApplicationEvent.hpp"
#include "Violet/Log.hpp"

using namespace Violet;

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


Application::Application(){
    m_Window = std::unique_ptr<Window>(Window::create());
    m_Window->setEventCallback(BIND_EVENT_FN(onEvent));

}

Application::~Application(){

}

void Application::run(){
    WindowResizeEvent e(1200, 720);
    VGE_TRACE(e.toString());

    while (m_Running){
        for(Layer* layer: m_LayerStack)
            layer->onUpdate();

        m_Window->onUpdate();
    }
}

void Application::onEvent(Event& e){
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

    VGE_CORE_INFO("{0}", e.toString());

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
