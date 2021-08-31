#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Violet/Platform/OpenGL/OpenGLContext.hpp"
#include "Violet/Log.hpp"


using namespace Violet;

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    :m_WindowHandle(windowHandle){
    VGE_CORE_ASSERT(windowHandle, "Window handle is null!")
}

void OpenGLContext::init() {
    glfwMakeContextCurrent(m_WindowHandle);

    //glad initialization
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    VGE_CORE_ASSERT(status, "Failed to initialize Glad!");
}

void OpenGLContext::swapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}
