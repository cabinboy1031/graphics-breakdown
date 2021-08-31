#ifndef VIOLET_OPENGLCONTEXT_H_
#define VIOLET_OPENGLCONTEXT_H_
#include "Violet/Renderer/RenderingContext.hpp"

class GLFWwindow;

namespace Violet{
    class OpenGLContext: public RenderingContext{
        public:
            OpenGLContext(GLFWwindow* windowHandle);

            virtual void init();
            virtual void swapBuffers();
        private:
            GLFWwindow* m_WindowHandle;
    };
}


#endif // VIOLET_OPENGLCONTEXT_H_
