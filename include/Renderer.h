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
    void OnResize(int newWidth, int newHeight);

private:
    void drawGrid();
    std::vector<float> initGrid();

private:
    const int cells = 20;
    const float cellSize = 32.0f;

    const float boardSize  = cells * cellSize;

    glm::mat4 proj, model;

    std::unique_ptr<ShaderProgram> pGridShaderProgram;
    std::unique_ptr<Mesh> pGridMesh;
};

#endif //RENDER_H
