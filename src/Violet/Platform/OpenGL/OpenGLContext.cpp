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
    VGE_CORE_TRACE("Glad initialized successfully!");

    VGE_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
    VGE_CORE_INFO("  Vendor:  {0}", glGetString(GL_VENDOR));
    VGE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::swapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}
