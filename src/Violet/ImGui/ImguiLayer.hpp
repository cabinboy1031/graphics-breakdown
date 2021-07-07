#ifndef __VIOLET_IMGUILAYER_H_
#define __VIOLET_IMGUILAYER_H_

#include "vgepch.hpp"
#include "Violet/Layer.hpp"

#include "imgui.h"
#include "Violet/Platform/OpenGL/ImguiOpenGLRenderer.hpp"

namespace Violet{
    class ImguiLayer: public Layer{
        public:
            ImguiLayer()
                :Layer("ImguiLayer") {}
            virtual void onAttach();
            virtual void onDetach();
            virtual void onUpdate();
            virtual void onEvent(Event& event);
    };
}


#endif // __IMGUILAYER_H_
