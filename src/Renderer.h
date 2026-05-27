#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

#include "ShaderProgram.h"

class Renderer
{
public:
    Renderer();
    
    void Draw();

private:
    void bindGrid();
    void drawGrid();
    void initGrid();

private:
    std::vector<float> vertices;

    const int cols = 20;
    const int rows = 20;
    const float cell = 32.0f;

    const float width  = cols * cell;
    const float height = rows * cell;

    glm::mat4 proj = glm::ortho(
    0.0f,
    width,
    height,
    0.0f);

    std::unique_ptr<ShaderProgram> gridShaderProgram;

    GLuint VAO;
};

#endif //RENDER_H
