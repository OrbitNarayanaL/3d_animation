#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Selection.h"

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
    int m_selectedVertexIndex;

    Mesh();
    ~Mesh();

    bool LoadOBJ(const std::string& filePath);
    void SetupMeshBuffers();
    void Draw() const;
    void Shutdown();

    int FindClosestVertexRay(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, float maxDistance = 100.0f);
    void DeformSelectedVertex(const glm::vec3& deltaOffset);
};
