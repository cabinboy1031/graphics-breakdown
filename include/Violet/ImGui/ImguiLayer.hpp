#ifndef __VIOLET_IMGUILAYER_H_
#define __VIOLET_IMGUILAYER_H_

#include "Violet/Layer.hpp"

namespace Violet{
    class ImguiLayer: public Layer{
        public:
            ImguiLayer()
                :Layer("ImguiLayer") {}
            ~ImguiLayer();

            virtual void onAttach();
            virtual void onDetach();
            virtual void onUpdate();
            virtual void onEvent(Event& event);

        private:
            float m_Time = 0.0f;
    };
}


#endif // __IMGUILAYER_H_
