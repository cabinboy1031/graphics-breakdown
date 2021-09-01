#ifndef VIOLET_SHADER_H_
#define VIOLET_SHADER_H_
#include <string>

namespace Violet{
    class Shader{
        public:
            Shader(const std::string& vertexSrc,
                   const std::string fragmentsrc);
            ~Shader();

            void bind() const;
            void unbind() const;
        private:
            uint32_t m_RendererID;
    };
}


#endif // VIOLET_SHADER_H_
