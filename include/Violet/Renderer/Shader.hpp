#ifndef VIOLET_SHADER_H_
#define VIOLET_SHADER_H_
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Violet/Log.hpp"

namespace Violet{
    class Shader{
        public:
            virtual ~Shader() {}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual void uploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

            static Shader* create(const std::string vertexSrc, const std::string fragmentSrc);
    };
}


#endif // VIOLET_SHADER_H_
