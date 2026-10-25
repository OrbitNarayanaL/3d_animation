#include "Mesh.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <tuple>

Mesh::Mesh() : VAO(0), VBO(0), EBO(0), m_buffersInitialized(false)
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

    // Simple triangulation - assume triangles
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

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // TexCoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
    m_buffersInitialized = true;
}

void Mesh::Draw() const
{
    if (!m_buffersInitialized || VAO == 0) return;
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
    m_buffersInitialized = false;
}
