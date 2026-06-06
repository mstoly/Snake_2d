#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices)
{
    _vertices = vertices;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        _vertices.size() * sizeof(float),
        _vertices.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        (void *)0);

    glEnableVertexAttribArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::Draw(GLint location, const GLfloat *value)
{
        glUniformMatrix4fv(
        location,
        1,
        GL_FALSE,
        value);

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_LINES,
        0,
        _vertices.size() / 2);
}
