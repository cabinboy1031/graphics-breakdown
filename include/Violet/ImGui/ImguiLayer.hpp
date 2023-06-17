#ifndef __VIOLET_IMGUILAYER_H_
#define __VIOLET_IMGUILAYER_H_

#include "Violet/Events/Event.hpp"
#include "Violet/Events/ApplicationEvent.hpp"
#include "Violet/Events/KeyEvent.hpp"
#include "Violet/Events/MouseEvent.hpp"
#include "Violet/Layer.hpp"

namespace Violet{
    class ImguiLayer: public Layer{
        public:
            ImguiLayer()
                :Layer("ImguiLayer") {}
            ~ImguiLayer();

            virtual void onAttach();
            virtual void onDetach();
            virtual void onImguiRender(Timestep);

            void begin();
            void end();

        private:
            float m_Time = 0.0f;
    };
}


#endif // __IMGUILAYER_H_
