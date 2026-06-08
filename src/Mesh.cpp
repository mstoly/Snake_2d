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

void Mesh::Draw(GLint projection, const GLfloat *valueProjection, GLint model, const GLfloat *valueModel)
{
    glUniformMatrix4fv(
        projection,
        1,
        GL_FALSE,
        valueProjection);

    glUniformMatrix4fv(
        model,
        1,
        GL_FALSE,
        valueModel);

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_LINES,
        0,
        _vertices.size() / 2);
}
