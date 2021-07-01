#ifndef __VIOLET_GL_APPLICATION_HPP__
#define __VIOLET_GL_APPLICATION_HPP__

#include "vgepch.hpp"
#include "Core.hpp"
#include "Violet/Window.hpp"

namespace VIOLET_API Violet{
    class Application {
        public:
            Application();
            virtual ~Application();

            void run();
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}



#endif
