#include "Violet/Platform/Linux/LinuxInput.hpp"
#include "Violet/Application.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
using namespace Violet;

Input* Input::s_Instance = new LinuxInput();

bool LinuxInput::isKeyPressedImpl(KeyCode code){
    auto window = Application::get().getWindow().getNativeWindow();
    auto state = glfwGetKey((GLFWwindow*)window, code);

    return state == GLFW_PRESS
        || state == GLFW_REPEAT;
}

bool LinuxInput::isMouseButtonPressedImpl(MouseButton button){
    auto window = Application::get().getWindow().getNativeWindow();
    auto state = glfwGetMouseButton((GLFWwindow*)window, (int)button);

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
