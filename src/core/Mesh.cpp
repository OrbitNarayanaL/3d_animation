#include "Mesh.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <tuple>
#include <limits>
#include <algorithm>
#include <glm/glm.hpp>
#include <cmath>

Mesh::Mesh() : VAO(0), VBO(0), EBO(0), m_selectedVertexIndex(-1)
{
}

Mesh::~Mesh()
{
    Shutdown();
}

bool Mesh::LoadOBJ(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open OBJ file: " << filePath << std::endl;
        return false;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<std::tuple<int,int,int> > faces;

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
        {
            float x, y, z;
            ss >> x >> y >> z;
            positions.push_back(glm::vec3(x, y, z));
        }
        else if (prefix == "vt")
        {
            float u, v;
            ss >> u >> v;
            texCoords.push_back(glm::vec2(u, v));
        }
        else if (prefix == "vn")
        {
            float x, y, z;
            ss >> x >> y >> z;
            normals.push_back(glm::vec3(x, y, z));
        }
        else if (prefix == "f")
        {
            std::string vertexStr;
            while (ss >> vertexStr)
            {
                int p = -1, t = -1, n = -1;
                size_t slash1 = vertexStr.find('/');
                if (slash1 == std::string::npos)
                {
                    p = std::stoi(vertexStr);
                }
                else
                {
                    p = std::stoi(vertexStr.substr(0, slash1));
                    size_t slash2 = vertexStr.find('/', slash1 + 1);
                    if (slash2 == std::string::npos)
                    {
                        if (slash1 + 1 < vertexStr.length())
                            t = std::stoi(vertexStr.substr(slash1 + 1));
                    }
                    else
                    {
                        if (slash1 + 1 < slash2)
                            t = std::stoi(vertexStr.substr(slash1 + 1, slash2 - slash1 - 1));
                        if (slash2 + 1 < vertexStr.length())
                            n = std::stoi(vertexStr.substr(slash2 + 1));
                    }
                }
                faces.push_back(std::make_tuple(p, t, n));
            }
        }
    }

    vertices.clear();
    indices.clear();

    for (size_t i = 0; i < faces.size(); i += 3)
    {
        for (int j = 0; j < 3; ++j)
        {
            auto [pIdx, tIdx, nIdx] = faces[i + j];
            Vertex vert;
            if (pIdx > 0 && pIdx <= (int)positions.size())
                vert.position = positions[pIdx - 1];
            else
                vert.position = glm::vec3(0.0f);
            if (tIdx > 0 && tIdx <= (int)texCoords.size())
                vert.texCoords = texCoords[tIdx - 1];
            else
                vert.texCoords = glm::vec2(0.0f);
            if (nIdx > 0 && nIdx <= (int)normals.size())
                vert.normal = normals[nIdx - 1];
            else
                vert.normal = glm::vec3(0.0f, 0.0f, 1.0f);
            vertices.push_back(vert);
            indices.push_back((unsigned int)(vertices.size() - 1));
        }
    }

    m_basePositions.clear();
    for (const auto& v : vertices)
        m_basePositions.push_back(v.position);

    SetupMeshBuffers();
    return true;
}

void Mesh::SetupMeshBuffers()
{
    if (vertices.empty())
        return;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

void Mesh::Draw() const
{
    if (VAO == 0) return;
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::Shutdown()
{
    if (EBO != 0) glDeleteBuffers(1, &EBO);
    if (VBO != 0) glDeleteBuffers(1, &VBO);
    if (VAO != 0) glDeleteVertexArrays(1, &VAO);
    VAO = VBO = EBO = 0;
}

int Mesh::FindClosestVertexRay(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, float maxDistance)
{
    m_selectedVertexIndex = -1;
    if (indices.size() < 3 || vertices.empty()) return -1;

    float closestDist = std::numeric_limits<float>::max();
    int closestVertex = -1;

    Ray ray{rayOrigin, rayDirection};
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        unsigned int i0 = indices[i];
        unsigned int i1 = indices[i + 1];
        unsigned int i2 = indices[i + 2];
        const glm::vec3& v0 = vertices[i0].position;
        const glm::vec3& v1 = vertices[i1].position;
        const glm::vec3& v2 = vertices[i2].position;
        float t, u, v;
        if (RayTriangleIntersect(ray, v0, v1, v2, t, u, v))
        {
            if (t < closestDist && t <= maxDistance)
            {
                closestDist = t;
                float d0 = glm::distance(v0, rayOrigin + rayDirection * t);
                float d1 = glm::distance(v1, rayOrigin + rayDirection * t);
                float d2 = glm::distance(v2, rayOrigin + rayDirection * t);
                if (d0 <= d1 && d0 <= d2) closestVertex = (int)i0;
                else if (d1 <= d0 && d1 <= d2) closestVertex = (int)i1;
                else closestVertex = (int)i2;
            }
        }
    }
    m_selectedVertexIndex = closestVertex;
    return m_selectedVertexIndex;
}

void Mesh::DeformSelectedVertex(const glm::vec3& deltaOffset)
{
    if (m_selectedVertexIndex < 0 || m_selectedVertexIndex >= (int)vertices.size()) return;
    vertices[m_selectedVertexIndex].position += deltaOffset;
    if (VBO != 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, m_selectedVertexIndex * sizeof(Vertex), sizeof(glm::vec3), &vertices[m_selectedVertexIndex].position);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Mesh::ApplySculptBrush(const glm::vec3& brushCenter, float radius, float strength, const std::string& brushType, const glm::vec3& mouseDragDelta)
{
    if (vertices.empty() || radius <= 0.0f) return;

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        float dist = glm::distance(vertices[i].position, brushCenter);
        if (dist > radius) continue;
        float falloff = 1.0f - (dist / radius);
        falloff = falloff * falloff;

        if (brushType == "Inflate")
        {
            glm::vec3 normal = vertices[i].normal;
            if (glm::length(normal) < 0.0001f) normal = glm::vec3(0.0f, 0.0f, 1.0f);
            vertices[i].position += glm::normalize(normal) * strength * falloff;
        }
        else if (brushType == "Smooth")
        {
            glm::vec3 avg = vertices[i].position;
            int count = 1;
            for (size_t j = 0; j < vertices.size() && count < 8; ++j)
            {
                if (i == j) continue;
                if (glm::distance(vertices[i].position, vertices[j].position) < radius * 0.3f)
                {
                    avg += vertices[j].position;
                    count++;
                }
            }
            avg /= (float)count;
            vertices[i].position = glm::mix(vertices[i].position, avg, strength * falloff * 0.5f);
        }
        else if (brushType == "Grab")
        {
            vertices[i].position += mouseDragDelta * strength * falloff;
        }
    }

    RecalculateNormals();

    if (VBO != 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Mesh::RecalculateNormals()
{
    if (indices.empty() || vertices.empty()) return;

    std::vector<glm::vec3> normalsAccum(vertices.size(), glm::vec3(0.0f));

    for (size_t i = 0; i < indices.size(); i += 3)
    {
        unsigned int i0 = indices[i];
        unsigned int i1 = indices[i + 1];
        unsigned int i2 = indices[i + 2];
        glm::vec3 edge1 = vertices[i1].position - vertices[i0].position;
        glm::vec3 edge2 = vertices[i2].position - vertices[i0].position;
        glm::vec3 faceNormal = glm::cross(edge1, edge2);
        normalsAccum[i0] += faceNormal;
        normalsAccum[i1] += faceNormal;
        normalsAccum[i2] += faceNormal;
    }

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        if (glm::length(normalsAccum[i]) > 0.0001f)
            vertices[i].normal = glm::normalize(normalsAccum[i]);
    }
}

void Mesh::AddBlendShape(const std::string& name, const std::vector<glm::vec3>& offsets)
{
    BlendShape bs;
    bs.name = name;
    bs.offsets = offsets;
    if (bs.offsets.size() != vertices.size() && !m_basePositions.empty() && bs.offsets.size() == m_basePositions.size())
    {
        // keep as is
    }
    m_blendShapes.push_back(bs);
    m_shapeWeights[name] = 0.0f;
}

void Mesh::SetBlendShapeWeight(const std::string& name, float weight)
{
    m_shapeWeights[name] = weight;
    UpdateMorphGeometry();
}

void Mesh::UpdateMorphGeometry()
{
    if (m_basePositions.empty() || vertices.empty()) return;
    size_t count = std::min(m_basePositions.size(), vertices.size());

    for (size_t i = 0; i < count; ++i)
    {
        glm::vec3 result = m_basePositions[i];
        for (const auto& bs : m_blendShapes)
        {
            auto it = m_shapeWeights.find(bs.name);
            float w = 0.0f;
            if (it != m_shapeWeights.end()) w = it->second;
            if (w == 0.0f) continue;
            if (i < bs.offsets.size())
                result += bs.offsets[i] * w;
        }
        vertices[i].position = result;
    }

    RecalculateNormals();

    if (VBO != 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
