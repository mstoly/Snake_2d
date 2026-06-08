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

    pGridShaderProgram = std::make_unique<ShaderProgram>("shaders/grid.vert", "shaders/grid.frag");

    std::vector<float> vertices = initGrid();
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

    float scaleX = minsize / newWidth;
    float scaleY = minsize / newHeight;
 
    float offsetX = (1 - scaleX) * boardSize * 0.5f;
    float offsetY = (1 - scaleY) * boardSize * 0.5f;

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(offsetX, offsetY, 0.0f));
    model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));
}

void Renderer::drawGrid()
{
    pGridShaderProgram->Use();
    pGridShaderProgram->UniformMatrix("uProj", proj);
    pGridShaderProgram->UniformMatrix("uModel", model);

    pGridMesh->Draw();
}

std::vector<float> Renderer::initGrid()
{
    std::vector<float> vertices;

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

    return vertices;
}
