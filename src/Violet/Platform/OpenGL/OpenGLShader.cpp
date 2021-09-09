#include "Violet/Platform/OpenGL/OpenGLShader.hpp"
#include "Violet/Log.hpp"

#include <vector>
#include "glad/glad.h"

using namespace Violet;

OpenGLShader::OpenGLShader(const std::string vertexSrc,
                           const std::string fragmentSrc){
    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

// Send the vertex shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    const GLchar *source = (const GLchar *)vertexSrc.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

// Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        //
        VGE_CORE_ERROR("{0}", infoLog.data());
        VGE_CORE_ASSERT(false, "Vertex shader compilation failed!");

        // In this simple program, we'll just leave
        return;
    }

// Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

// Send the fragment shader source code to GL
// Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *)fragmentSrc.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

// Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        VGE_CORE_ERROR("{0}", infoLog.data());
        VGE_CORE_ASSERT(false, "Fragment shader compilation failed!");

        // In this simple program, we'll just leave
        return;
    }

// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a program object.
    GLuint program = glCreateProgram();

// Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

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
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.
        VGE_CORE_ERROR("{0}", infoLog.data());
        VGE_CORE_ASSERT(false, "shader program linking failed!");

        // In this simple program, we'll just leave
        return;
    }

// Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    m_RendererID = program;
}

OpenGLShader::~OpenGLShader(){
    VGE_CORE_TRACE("Deleting shader.")
    glDeleteProgram(m_RendererID);
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
