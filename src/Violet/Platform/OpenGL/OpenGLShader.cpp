#include "Violet/Platform/OpenGL/OpenGLShader.hpp"
#include "Violet/Log.hpp"

#include <fstream>
#include <vector>
#include "glad/glad.h"

using namespace Violet;

static GLenum shaderTypeFromString(const std::string type){
    if(type == "vertex") return GL_VERTEX_SHADER;
    if(type == "fragment") return GL_FRAGMENT_SHADER;
    if(type == "geometry") return GL_GEOMETRY_SHADER;
    if(type == "compute") return GL_COMPUTE_SHADER;

    VGE_CORE_ASSERT(false, "Unknown shader type!");
    return 0;
}

OpenGLShader::OpenGLShader(const std::string vertexSrc,
                           const std::string fragmentSrc){
    VGE_CORE_TRACE("Loading shader from hardcoded string.")
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;

    compile(sources);
}

OpenGLShader::OpenGLShader(const std::string filepath){
    std::string shaderSrc = readFile(filepath);
    auto shaderSources = preProcess(shaderSrc);

    compile(shaderSources);
    VGE_CORE_TRACE("Shader {0} compiled!", filepath.c_str());
}

OpenGLShader::~OpenGLShader(){
    VGE_CORE_TRACE("Deleting shader.")
    glDeleteProgram(m_RendererID);
}

std::string OpenGLShader::readFile(const std::string filepath){
    VGE_CORE_TRACE("Reading file: {0}...", filepath.c_str());
    std::string result;
    std::ifstream in;
    in.open(filepath.c_str(), std::ios::binary);
    if(in){
        in.seekg(0,std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0],result.size());
        in.close();
    } else {
        VGE_CORE_ERROR("Could not open file '{0}'", filepath);
    }
    return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string source){
    VGE_CORE_TRACE("Preprocessing source...")
    std::unordered_map<GLenum, std::string> shaderSources;

    const char* typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);
    while(pos != std::string::npos){
        size_t eol = source.find_first_of("\n", pos);
        VGE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);
        VGE_CORE_ASSERT(type == "vertex" || type == "fragment", "Unsupported shader type specification");

        size_t nextLinePos = source.find_first_not_of("\n", eol);
        pos = source.find(typeToken,nextLinePos);
        shaderSources[shaderTypeFromString(type)] = source.substr(nextLinePos,
                                                                  pos - (nextLinePos == std::string::npos ? source.size() - 1: nextLinePos));
    }

    return shaderSources;
}

void OpenGLShader::compile(std::unordered_map<GLenum, std::string> shaderSources){
    GLuint program = glCreateProgram();
    std::vector<GLenum> glShaderIDs(shaderSources.size());

    for (auto&& [key, value] : shaderSources){
        GLenum type = key;
        const std::string& source = value;

        GLuint shader = glCreateShader(type);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
        const GLchar *sourcecstr = (const GLchar*)source.c_str();
        glShaderSource(shader, 1, &sourcecstr, 0);

    // Compile the vertex shader
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(shader);

            // Use the infoLog as you see fit.
            //
            VGE_CORE_ERROR("{0}", infoLog.data());
            VGE_CORE_ASSERT(false, "Shader compilation failed!");

            // In this simple program, we'll just leave
            return;
        }
        glAttachShader(program, shader);
        glShaderIDs.push_back(shader);
    }
// Link our program
    glLinkProgram(program);

// Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        for(auto id : glShaderIDs){
            glDeleteShader(id);
        }

        // Use the infoLog as you see fit.
        VGE_CORE_ERROR("{0}", infoLog.data());
        VGE_CORE_ASSERT(false, "shader program linking failed!");

        // In this simple program, we'll just leave
        return;
    }

// Always detach shaders after a successful link.
    for(auto id : glShaderIDs){
        glDetachShader(program, id);

    }
    m_RendererID = program;
}

void OpenGLShader::bind() const {
    glUseProgram(m_RendererID);
}

void OpenGLShader::unbind() const {
    glUseProgram(0);
}

void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix){
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::uploadUniformFloat (const std::string &name, const float in){
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1f(location, in);
}
void OpenGLShader::uploadUniformFloat2(const std::string &name, const glm::vec2& vector){
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform2f(location, vector.x, vector.y);
}
void OpenGLShader::uploadUniformFloat3(const std::string &name, const glm::vec3& vector){
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void OpenGLShader::uploadUniformFloat4(const std::string &name, const glm::vec4& vector){
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void OpenGLShader::uploadUniformInt (const std::string &name, const int in){
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(location, in);
}
