#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"

Renderer::Renderer()
{
    proj = glm::ortho(
    0.0f,
    boardSize,
    boardSize,
    0.0f);

    model = glm::mat4(1.0f);

    initGrid();

    pGridShaderProgram = std::make_unique<ShaderProgram>("shaders/grid.vert", "shaders/grid.frag");
    pGridMesh = std::make_unique<Mesh>(vertices);
}

Renderer::~Renderer()
{
}

void Renderer::Draw()
{
    drawGrid();
}

void Renderer::OnResize(int newWidth, int newHeight)
{
    glViewport(0, 0, newWidth, newHeight);

    float minsize = std::min(newWidth, newHeight);
    float scale = minsize / boardSize;

    float offsetX = (newWidth - minsize) * 0.5f / scale;
    float offsetY = (newHeight - minsize) * 0.5f / scale;
    float scaleX = minsize / newWidth;
    float scaleY = minsize / newHeight;

    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));
    model = glm::translate(model, glm::vec3(offsetX, offsetY, 0.0f));
}

void Renderer::drawGrid()
{
    pGridShaderProgram->Use();
    pGridShaderProgram->UniformMatrix("uProj", proj);
    pGridShaderProgram->UniformMatrix("uModel", model);

    pGridMesh->Draw();
}

void Renderer::initGrid()
{
    for (int x = 0; x <= cells; ++x)
    {
        float px = x * cellSize;

        vertices.push_back(px);
        vertices.push_back(0.0f);

        vertices.push_back(px);
        vertices.push_back(boardSize);
    }

    for (int y = 0; y <= cells; ++y)
    {
        float py = y * cellSize;

        vertices.push_back(0.0f);
        vertices.push_back(py);

        vertices.push_back(boardSize);
        vertices.push_back(py);
    }
}
