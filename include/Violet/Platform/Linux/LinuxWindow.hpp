#ifndef __VIOLET_LINUXWINDOW_H_
#define __VIOLET_LINUXWINDOW_H_

#include "vgepch.hpp"
#include "Violet/Window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Violet/Events/ApplicationEvent.hpp"
#include "Violet/Events/MouseEvent.hpp"
#include "Violet/Events/KeyEvent.hpp"


namespace Violet{
    class LinuxWindow: public Window {
        public:
            LinuxWindow(const WindowProps& props);
            virtual ~LinuxWindow();

            void onUpdate() override;

            inline unsigned int getWidth() const override { return m_Data.width; }
            inline unsigned int getHeight() const override { return m_Data.height; }

            inline void setEventCallback(const EventCallBackFn& callback) override
            { m_Data.eventCallback = callback; }
            void setVSync(bool enabled) override;
            bool isVSync() const override;
        private:
            virtual void init(const WindowProps& props);
            virtual void shutdown();
        private:
            GLFWwindow* m_Window;

            struct WindowData {
                std::string title;
                uint32_t width, height;
                bool vSync;

                EventCallBackFn eventCallback;
                } m_Data;
    };
}


#endif // __LINUXWINDOW_H_
