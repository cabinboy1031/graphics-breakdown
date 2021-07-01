#ifndef __VIOLET_GL_APPLICATION_HPP__
#define __VIOLET_GL_APPLICATION_HPP__

#include "vgepch.hpp"
#include "Core.hpp"

namespace VIOLET_API Violet{
    class Application {
        public:
            Application();
            virtual ~Application();

            void run();
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}



#endif
