#pragma once

#include <string>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Initialize(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void Clear();
    void RenderTriangle();
    void Shutdown();

private:
    unsigned int m_shaderProgram;
    unsigned int m_VAO;
    unsigned int m_VBO;

    unsigned int CompileShader(const std::string& source, unsigned int type);
    unsigned int CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
    std::string LoadShaderSource(const std::string& filePath);
};
