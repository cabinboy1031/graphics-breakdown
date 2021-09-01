#ifndef VIOLET_RENDERER_API_H
#define VIOLET_RENDERER_API_H

namespace Violet{
    enum class RendererAPI {
    None = 0,
    OpenGL = 1
    };

    class Renderer{
        public:
            inline static RendererAPI getAPI() { return s_RendererAPI; }
            inline static void setAPI(RendererAPI api) { s_RendererAPI = api; }
        private:
            static RendererAPI s_RendererAPI;
    };
}


#endif // VIOLET_RENDERER_API_H
