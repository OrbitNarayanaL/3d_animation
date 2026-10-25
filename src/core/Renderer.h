#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Rigging.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Initialize(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& objPath = "");
    void Clear();
    void RenderTriangle();
    void RenderSkeletonDebug();
    void Shutdown();
    Mesh& GetMesh() { return m_mesh; }
    Skeleton& GetSkeleton() { return m_skeleton; }

    void SetAlbedoColor(const glm::vec3& color) { m_albedoColor = color; }
    void SetRoughness(float r) { m_roughness = r; }
    void SetMetalness(float m) { m_metalness = m; }
    void SetVisualizeUV(int value) { m_visualizeUV = value; }

private:
    unsigned int m_shaderProgram;
    Mesh m_mesh;
    Skeleton m_skeleton;

    glm::vec3 m_albedoColor = glm::vec3(0.8f, 0.5f, 0.2f);
    float m_roughness = 0.5f;
    float m_metalness = 0.0f;
    int m_visualizeUV = 0;

    unsigned int CompileShader(const std::string& source, unsigned int type);
    unsigned int CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
    std::string LoadShaderSource(const std::string& filePath);
};
