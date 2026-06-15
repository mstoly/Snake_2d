#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices);
    virtual ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void Draw();

private:
    GLuint VAO{};
    GLuint VBO{};
    int verticesSize{};
};

#endif //MESH_H