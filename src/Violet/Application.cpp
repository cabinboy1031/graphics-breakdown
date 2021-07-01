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
        m_Window->onUpdate();
    }
}

void Application::onEvent(Event& e){
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
    VGE_CORE_INFO("{0}", e.toString());
}

bool Application::onWindowClose(WindowCloseEvent& e){
    m_Running = false;
    return true;
}
