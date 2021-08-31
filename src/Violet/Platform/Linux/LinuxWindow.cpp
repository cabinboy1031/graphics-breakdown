#include "Violet/Platform/Linux/LinuxWindow.hpp"
#include "Violet/Platform/OpenGL/OpenGLContext.hpp"
#include "GLFW/glfw3.h"

using namespace Violet;

namespace Violet{
    static bool s_GLFWInit = false;
    static void GLFWErrorCallback(int error, const char* description){
        VGE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }
}

Window* Window::create(const WindowProps& props){
    return new LinuxWindow(props);
}

LinuxWindow::LinuxWindow(const WindowProps& props){
    init(props);
}

LinuxWindow::~LinuxWindow(){

    shutdown();
}

void LinuxWindow::init(const WindowProps& props) {
    m_Data.title = props.title;
    m_Data.width = props.width;
    m_Data.height = props.height;

    VGE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

    // initializing glfw
    if(!s_GLFWInit){
        int success = glfwInit();
        VGE_CORE_ASSERT(success, "Could not initialize GLFW!");

        s_GLFWInit = true;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    VGE_CORE_TRACE("GLFW initialized successfully:");
    VGE_CORE_INFO ("GLFW version: {0}", glfwGetVersionString());


    // window creation
    m_Window = glfwCreateWindow((int)props.width, (int)props.height, m_Data.title.c_str(), nullptr, nullptr);

    m_Context = new OpenGLContext(m_Window);
    m_Context->init();

    //glfw additional settings
    glfwSetWindowUserPointer(m_Window, &m_Data);
    setVSync(true);

    //set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.eventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.eventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch(action){
            case GLFW_PRESS:{
                KeyPressedEvent event(key,0);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:{
                KeyReleasedEvent event(key);
                data.eventCallback(event);
                break;
            }
            case GLFW_REPEAT:{
                KeyPressedEvent event(key,1);
                data.eventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.eventCallback(event);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch(action){
            case GLFW_PRESS:{
                MouseButtonPressedEvent event(button);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:{
                MouseButtonReleasedEvent event(button);
                data.eventCallback(event);
                break;
            }

        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset,double yOffset){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.eventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPosition, double yPosition){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPosition, (float)yPosition);
        data.eventCallback(event);
    });
}

void LinuxWindow::shutdown(){
    VGE_CORE_TRACE("GLFW shutting down.");
    glfwDestroyWindow(m_Window);
}

void LinuxWindow::onUpdate(){
    glfwPollEvents();
    m_Context->swapBuffers();
}

void LinuxWindow::setVSync(bool enabled){
    if (enabled) glfwSwapInterval(1);
    else glfwSwapInterval(0);

    m_Data.vSync = enabled;
}

bool LinuxWindow::isVSync() const {
    return m_Data.vSync;
}
