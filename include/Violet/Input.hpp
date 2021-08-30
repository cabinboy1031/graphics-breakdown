#ifndef VIOLET_INPUT_H_
#define VIOLET_INPUT_H_
#include "Violet/Core.hpp"
#include <utility>

namespace Violet {
    class Input{
        public:
            inline static bool isKeyPressed(int keycode){
                return s_Instance->isKeyPressedImpl(keycode);
            }
            inline static bool isMouseButtonPressed(int button){
                return s_Instance->isMouseButtonPressedImpl(button);
            }
            inline static std::pair<float, float> getMousePosition(){
                return s_Instance->getMousePositionImpl();
            }
            inline static bool getMouseX(){return s_Instance->getMouseXImpl();}
            inline static bool getMouseY(){return s_Instance->getMouseYImpl();}
        protected:
            virtual bool isKeyPressedImpl(int keycode) = 0;
            virtual bool isMouseButtonPressedImpl(int button) = 0;
            virtual std::pair<float, float> getMousePositionImpl() = 0;
            virtual float getMouseXImpl() = 0;
            virtual float getMouseYImpl() = 0;
        private:
            static Input* s_Instance;
    };
}


#endif // INPUT_H_
