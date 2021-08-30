#ifndef __VIOLET_WINDOW_H_
#define __VIOLET_WINDOW_H_

#include "vgepch.hpp"
#include "Violet/Events/Event.hpp"
#include "Violet/Log.hpp"

namespace Violet{
    struct WindowProps {
        std::string title;
        uint32_t width;
        uint32_t height;

        WindowProps(const std::string& title = "Violet Engine",
                    uint32_t width = 1920,
                    uint32_t height = 1080) {
            this->title = title;
            this->width = width;
            this->height = height;
        }
    };

    class Window {
        public:
            using EventCallBackFn = std::function<void(Event&)>;

            virtual ~Window() {}

            virtual void onUpdate() = 0;

            virtual unsigned int getWidth() const = 0;
            virtual unsigned int getHeight() const = 0;

            virtual void setEventCallback(const EventCallBackFn& callback) = 0;
            virtual void setVSync(bool enabled) = 0;
            virtual bool isVSync() const = 0;

            static Window* create(const WindowProps& props = WindowProps());

            virtual void* getNativeWindow() const = 0;
    };
}


#endif // __WINDOW_H_
