#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"

Renderer::Renderer()
{
    proj = glm::ortho(
    0.0f,
    width,
    height,
    0.0f);

    initGrid();
    bindGrid();

    gridShaderProgram = std::make_unique<ShaderProgram>("shaders/grid.vert", "shaders/grid.frag");
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::Draw()
{
    drawGrid();
}

void Renderer::bindGrid()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
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

void Renderer::drawGrid()
{
    gridShaderProgram->Use();

    glUniformMatrix4fv(
        glGetUniformLocation(gridShaderProgram->GetId(), "uProj"),
        1,
        GL_FALSE,
        glm::value_ptr(proj));

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_LINES,
        0,
        vertices.size() / 2);
}

void Renderer::initGrid()
{
    for (int x = 0; x <= cols; ++x)
    {
        float px = x * cell;

        vertices.push_back(px);
        vertices.push_back(0.0f);

        vertices.push_back(px);
        vertices.push_back(height);
    }

    for (int y = 0; y <= rows; ++y)
    {
        float py = y * cell;

        vertices.push_back(0.0f);
        vertices.push_back(py);

        vertices.push_back(width);
        vertices.push_back(py);
    }
}
