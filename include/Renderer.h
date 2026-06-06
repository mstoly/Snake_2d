#ifndef RENDER_H
#define RENDER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

#include "ShaderProgram.h"
#include "Mesh.h"

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();
    
    void Draw();

private:
    void drawGrid();
    void initGrid();

private:
    std::vector<float> vertices;

    const int cols = 20;
    const int rows = 20;
    const float cell = 32.0f;

    const float width  = cols * cell;
    const float height = rows * cell;

    glm::mat4 proj;

    std::unique_ptr<ShaderProgram> pGridShaderProgram;
    std::unique_ptr<Mesh> pGridMesh;
};

#endif //RENDER_H
