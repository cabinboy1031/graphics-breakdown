#ifndef VIOLET_INPUT_H_
#define VIOLET_INPUT_H_
#include "Violet/Core.hpp"
#include "Violet/InputCodes.hpp"
#include <utility>

namespace Violet {

    class Input{
        public:
            inline static bool isKeyPressed(KeyCode code){
                return s_Instance->isKeyPressedImpl(code);
            }
            inline static bool isMouseButtonPressed(MouseButton button){
                return s_Instance->isMouseButtonPressedImpl(button);
            }
            inline static std::pair<float, float> getMousePosition(){
                return s_Instance->getMousePositionImpl();
            }
            inline static bool getMouseX(){return s_Instance->getMouseXImpl();}
            inline static bool getMouseY(){return s_Instance->getMouseYImpl();}
        protected:
            virtual bool isKeyPressedImpl(KeyCode code) = 0;
            virtual bool isMouseButtonPressedImpl(MouseButton button) = 0;
            virtual std::pair<float, float> getMousePositionImpl() = 0;
            virtual float getMouseXImpl() = 0;
            virtual float getMouseYImpl() = 0;
        private:
            static Input* s_Instance;
    };
}




#endif // INPUT_H_
