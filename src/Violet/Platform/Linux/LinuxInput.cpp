#include "Violet/Platform/Linux/LinuxInput.hpp"
#include "Violet/Application.hpp"

#include <GLFW/glfw3.h>
using namespace Violet;

Input* Input::s_Instance = new LinuxInput();

bool LinuxInput::isKeyPressedImpl(int keycode){
    auto window = Application::get().getWindow().getNativeWindow();
    auto state = glfwGetKey((GLFWwindow*)window, keycode);

    return state == GLFW_PRESS || GLFW_REPEAT;
}

bool LinuxInput::isMouseButtonPressedImpl(int button){
    auto window = Application::get().getWindow().getNativeWindow();
    auto state = glfwGetMouseButton((GLFWwindow*)window, button);

    return state == GLFW_PRESS;
}

std::pair<float,float> LinuxInput::getMousePositionImpl(){
    auto window = Application::get().getWindow().getNativeWindow();
    double xpos, ypos;
    glfwGetCursorPos((GLFWwindow*)window, &xpos, &ypos);

    return std::pair<float, float>((float)xpos, (float)ypos);
}

float LinuxInput::getMouseXImpl(){
    auto[x,y] = getMousePositionImpl();
    return x;
}

float LinuxInput::getMouseYImpl(){
    auto[x,y] = getMousePositionImpl();
    return y;
}
