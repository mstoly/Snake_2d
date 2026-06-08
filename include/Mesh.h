#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices);
    virtual ~Mesh();

    void Draw(GLint projection, const GLfloat *valueProjection, GLint model, const GLfloat *valueModel);

private:
    GLuint VAO{};
    GLuint VBO{};
    std::vector<float> _vertices;
};

#endif //MESH_H