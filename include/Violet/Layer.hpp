#ifndef __VIOLET_LAYER_H_
#define __VIOLET_LAYER_H_

#include "Violet/Core.hpp"
#include "Violet/Core/Timestep.hpp"
#include "Violet/Events/Event.hpp"

namespace Violet {
    class Layer {
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer();

            virtual void onAttach() {}
            virtual void onDetach() {}
            virtual void onUpdate(Timestep deltaTime) {}
            virtual void onEvent(Event& event) {}
            virtual void onImguiRender(Timestep deltaTime) {};

            inline const std::string& getName() const { return m_DebugName; }
        protected:
            std::string m_DebugName;
    };
}

#endif // __LAYER_H_
