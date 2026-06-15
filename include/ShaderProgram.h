#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
    ShaderProgram(const char *vertexFile, const char *fragmentFile);
    virtual ~ShaderProgram();

    void Use();
    void UniformMatrix(const std::string & uniformNeme, glm::mat4x4& m);
    GLuint GetId(); 

private:
    void compileShader(GLuint& shader, const char * fileName);
    void build(GLuint &vertexShader, GLuint &fragmentShader);

private:
    const int static infoLogSize = 512;
    std::unordered_map<std::string, GLint> uniformMap;

    GLuint programId;
    
    char infoLog[infoLogSize];
};

#endif //SHADER_H