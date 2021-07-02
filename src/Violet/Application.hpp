#ifndef __VIOLET_GL_APPLICATION_HPP__
#define __VIOLET_GL_APPLICATION_HPP__

#include "vgepch.hpp"
#include "Core.hpp"

#include "Violet/Window.hpp"
#include "Violet/LayerStack.hpp"
#include "Violet/Events/ApplicationEvent.hpp"

namespace VIOLET_API Violet{
    class Application {
        public:
            Application();
            virtual ~Application();

            void run();

            void onEvent(Event& e);

            void pushLayer(Layer* layer);
            void pushOverlay(Layer* layer);
        private:
            bool onWindowClose(WindowCloseEvent &e);
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
            LayerStack m_LayerStack;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}



#endif
