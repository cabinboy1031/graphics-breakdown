#ifndef __VIOLET_GL_APPLICATION_HPP__
#define __VIOLET_GL_APPLICATION_HPP__

#include "Core.hpp"

#include "Violet/Window.hpp"
#include "Violet/LayerStack.hpp"
#include "Violet/ImGui/ImguiLayer.hpp"
#include "Violet/Events/ApplicationEvent.hpp"
#include "Violet/Core/Timestep.hpp"
#include "Violet/Renderer/Renderer.hpp"

#include "Violet/ImGui/ImguiLayer.hpp"

namespace [[VIOLET_API]] Violet{
    class Application {
        public:
            Application();
            virtual ~Application();

            void run();

            void onEvent(Event& e);
            void pushLayer(Layer* layer);
            void pushOverlay(Layer* layer);

            static inline Application& get() { return *s_Instance; }
            inline Window& getWindow() { return *m_Window; }
        private:
            bool onWindowClose(WindowCloseEvent &e);
            std::unique_ptr<Window> m_Window;
            ImguiLayer* m_ImguiLayer;

            bool m_Running = true;
            LayerStack m_LayerStack;
            static Application* s_Instance;

            float m_LastFrameTime;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}



#endif
