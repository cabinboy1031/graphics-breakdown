#ifndef VIOLET_LINUXINPUT_H_
#define VIOLET_LINUXINPUT_H_
#include "Violet/Input.hpp"

namespace Violet{
    class LinuxInput: public Input{
        protected:
            virtual bool isKeyPressedImpl(KeyCode code) override;
            virtual bool isMouseButtonPressedImpl(MouseButton button) override;
            virtual std::pair<float,float> getMousePositionImpl() override;
            virtual float getMouseXImpl() override;
            virtual float getMouseYImpl() override;
    };
}


#endif // LINUXINPUT_H_
