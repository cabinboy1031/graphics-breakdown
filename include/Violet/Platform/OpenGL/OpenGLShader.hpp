#ifndef VIOLET_OPENGL_SHADER_H_
#define VIOLET_OPENGL_SHADER_H_
#include "Violet/Renderer/Shader.hpp"

#include <string>
#include <unordered_map>

//TODO REMOVE!
typedef unsigned int GLenum;

namespace Violet{
    class OpenGLShader:public Shader{
        public:
            OpenGLShader(const std::string vertexSrc,
                         const std::string fragmentsrc);
            OpenGLShader(const std::string filePath);
            virtual ~OpenGLShader();

            virtual void bind() const;
            virtual void unbind() const;

            virtual void uploadUniformInt(const std::string& name,const int in);

            virtual void uploadUniformFloat (const std::string& name,const float in);
            virtual void uploadUniformFloat2(const std::string& name,const glm::vec2& vector);
            virtual void uploadUniformFloat3(const std::string& name,const glm::vec3& vector);
            virtual void uploadUniformFloat4(const std::string& name,const glm::vec4& vector);
            virtual void uploadUniformMat4(const std::string& name,const glm::mat4& matrix);
        private:
            void compile(std::unordered_map<GLenum, std::string> shaderSources);
            std::unordered_map<GLenum, std::string> preProcess(const std::string source);
            std::string readFile(const std::string filepath);
        private:
            uint32_t m_RendererID;
    };
}


#endif // VIOLET_SHADER_H_
