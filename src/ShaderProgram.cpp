#include <assert.h>
#include <filesystem>
#include <fstream>

#include "ShaderProgram.h"

namespace fs = std::filesystem;

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShader, vertexFile);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShader, fragmentFile);

    build(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::Use()
{
    glUseProgram(programId);
}

GLuint ShaderProgram::GetId()
{
    return programId;
}

void ShaderProgram::compileShader(GLuint &shader, const char *fileName)
{
    fs::path path{fileName};
    if (fs::exists(path))
    {
        auto size = fs::file_size(path);
        std::string buffer(size, '\0');

        std::ifstream file(path, std::ios::binary);
        if (file.read(buffer.data(), size))
        {
            int success;
            const char* src = buffer.c_str();
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                glGetShaderInfoLog(shader, infoLogSize, nullptr, infoLog);
                throw std::runtime_error(infoLog);
            }
        }
        else
        {
            throw std::runtime_error("Shader file can't be loaded");
        }
    }
    else
    {
        throw std::runtime_error("Shader file not found");
    }
}

void ShaderProgram::build(GLuint &vertexShader, GLuint &fragmentShader)
{
    int success;
    
    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);

    glLinkProgram(programId);
    glGetProgramiv(programId, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(programId, infoLogSize, nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }
}
