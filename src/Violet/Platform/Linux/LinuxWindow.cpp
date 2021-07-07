#include "LinuxWindow.hpp"

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

    // window creation
    m_Window = glfwCreateWindow((int)props.width, (int)props.height, m_Data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);

    //glad initialization
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    VGE_CORE_ASSERT(status, "Failed to initialize Glad!");
    VGE_CORE_TRACE("Glad initialized successfully!");
    GLint major = 0;
    GLint minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    VGE_CORE_TRACE("OpenGL version: {0}.{1}",major, minor);


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
    glfwDestroyWindow(m_Window);
}

void LinuxWindow::onUpdate(){
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void LinuxWindow::setVSync(bool enabled){
    if (enabled) glfwSwapInterval(1);
    else glfwSwapInterval(0);

    m_Data.vSync = enabled;
}

bool LinuxWindow::isVSync() const {
    return m_Data.vSync;
}
