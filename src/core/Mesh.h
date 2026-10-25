#pragma once

#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include "Selection.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::ivec4 boneIds;
    glm::vec4 boneWeights;
};

struct BlendShape
{
    std::string name;
    std::vector<glm::vec3> offsets;
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
    void ApplySculptBrush(const glm::vec3& brushCenter, float radius, float strength, const std::string& brushType, const glm::vec3& mouseDragDelta = glm::vec3(0.0f));
    void RecalculateNormals();

    void AddBlendShape(const std::string& name, const std::vector<glm::vec3>& offsets);
    void SetBlendShapeWeight(const std::string& name, float weight);
    void UpdateMorphGeometry();

private:
    std::vector<BlendShape> m_blendShapes;
    std::map<std::string, float> m_shapeWeights;
    std::vector<glm::vec3> m_basePositions;
};
