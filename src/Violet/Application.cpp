#include "Application.hpp"

#include "Violet/Events/ApplicationEvent.hpp"
#include "Violet/Log.hpp"

#include <GLFW/glfw3.h>

using namespace Violet;

Application::Application(){
    m_Window = std::unique_ptr<Window>(Window::create());

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
