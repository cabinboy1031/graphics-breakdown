#ifndef VIOLET_GRAPHICSCONTEXT_H_
#define VIOLET_GRAPHICSCONTEXT_H_

namespace Violet{
    class RenderingContext{
        public:
            virtual void init() = 0;
            virtual void swapBuffers() = 0;
    };
}


#endif // VIOLET_GRAPHICSCONTEXT_H_
