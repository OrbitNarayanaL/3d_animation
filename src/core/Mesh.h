#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    Mesh();
    ~Mesh();

    bool LoadOBJ(const std::string& filePath);
    void SetupMeshBuffers();
    void Draw() const;
    void Shutdown();

private:
    bool m_buffersInitialized;
};
