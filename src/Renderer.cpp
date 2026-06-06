#include <iostream>
#include <glad/glad.h>
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

void Renderer::drawGrid()
{
    pGridShaderProgram->Use();
    pGridMesh->Draw(glGetUniformLocation(pGridShaderProgram->GetId(), "uProj"), glm::value_ptr(proj));
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
