#include "Application.hpp"

#include "Violet/Events/ApplicationEvent.hpp"
#include "Violet/Log.hpp"

using namespace Violet;

Application::Application(){

}

Application::~Application(){

}

void Application::run(){
    WindowResizeEvent e(1200, 720);
    VGE_TRACE(e.toString());

    while (true){

    }
}
