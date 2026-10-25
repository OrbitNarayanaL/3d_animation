#pragma once

#include <string>
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
    void Shutdown();
    Mesh& GetMesh() { return m_mesh; }
    Skeleton& GetSkeleton() { return m_skeleton; }

private:
    unsigned int m_shaderProgram;
    Mesh m_mesh;
    Skeleton m_skeleton;

    unsigned int CompileShader(const std::string& source, unsigned int type);
    unsigned int CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
    std::string LoadShaderSource(const std::string& filePath);
};
