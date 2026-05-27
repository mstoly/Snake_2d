#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

class Shader
{
public:
    Shader(const char *vertexFile, const char *fragmentFile);

    void Use();
    GLuint GetProgramId(); 

private:
    void compileShader(GLuint& shader, const char * fileName);
    void compileProgram(GLuint &vertexShader, GLuint &fragmentShader);

private:
   const int static infoLogSize = 512;  

    GLuint programId;

    int success;
    char infoLog[infoLogSize];
};

#endif // SHADER_H