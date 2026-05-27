#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

class ShaderProgram
{
public:
    ShaderProgram(const char *vertexFile, const char *fragmentFile);

    void Use();
    GLuint GetId(); 

private:
    void compileShader(GLuint& shader, const char * fileName);
    void build(GLuint &vertexShader, GLuint &fragmentShader);

private:
   const int static infoLogSize = 512;  

    GLuint programId;

    int success;
    char infoLog[infoLogSize];
};

#endif // SHADER_H