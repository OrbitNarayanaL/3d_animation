#include "Renderer.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
    : m_shaderProgram(0)
{
}

Renderer::~Renderer()
{
    Shutdown();
}

std::string Renderer::LoadShaderSource(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

unsigned int Renderer::CompileShader(const std::string& source, unsigned int type)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        return 0;
    }
    return shader;
}

unsigned int Renderer::CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
    unsigned int vertexShader = CompileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);
    if (vertexShader == 0 || fragmentShader == 0)
        return 0;

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

bool Renderer::Initialize(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& objPath)
{
    std::string vertexSource = LoadShaderSource(vertexShaderPath);
    std::string fragmentSource = LoadShaderSource(fragmentShaderPath);
    m_shaderProgram = CreateShaderProgram(vertexSource, fragmentSource);
    if (m_shaderProgram == 0)
        return false;

    if (!objPath.empty())
    {
        m_mesh.LoadOBJ(objPath);
    }
    else
    {
        m_mesh.vertices.clear();
        m_mesh.indices.clear();
        Vertex v1, v2, v3;
        v1.position = glm::vec3(-0.5f, -0.5f, 0.0f);
        v2.position = glm::vec3(0.5f, -0.5f, 0.0f);
        v3.position = glm::vec3(0.0f, 0.5f, 0.0f);
        v1.normal = v2.normal = v3.normal = glm::vec3(0.0f, 0.0f, 1.0f);
        v1.texCoords = v2.texCoords = v3.texCoords = glm::vec2(0.0f);
        v1.boneIds = glm::ivec4(0);
        v1.boneWeights = glm::vec4(1.0f);
        v2.boneIds = glm::ivec4(0);
        v2.boneWeights = glm::vec4(1.0f);
        v3.boneIds = glm::ivec4(0);
        v3.boneWeights = glm::vec4(1.0f);
        m_mesh.vertices.push_back(v1);
        m_mesh.vertices.push_back(v2);
        m_mesh.vertices.push_back(v3);
        m_mesh.indices.push_back(0);
        m_mesh.indices.push_back(1);
        m_mesh.indices.push_back(2);
        m_mesh.SetupMeshBuffers();
    }

    // Initialize simple skeleton
    m_skeleton = Skeleton();
    m_skeleton.AddJoint("Root", -1, glm::mat4(1.0f));
    m_skeleton.UpdateJointTransforms(0, glm::mat4(1.0f));
    m_skeleton.ComputeInverseBindMatrices();

    return true;
}

void Renderer::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderTriangle()
{
    glUseProgram(m_shaderProgram);
    unsigned int location = glGetUniformLocation(m_shaderProgram, "uBoneTransforms");
    if (location != (unsigned int)-1 && !m_skeleton.joints.empty())
    {
        std::vector<glm::mat4> boneMatrices;
        for (const auto& joint : m_skeleton.joints)
        {
            boneMatrices.push_back(joint.globalTransform);
            if (boneMatrices.size() >= 100) break;
        }
        glUniformMatrix4fv(location, (GLsizei)boneMatrices.size(), GL_FALSE, glm::value_ptr(boneMatrices[0]));
    }
    m_mesh.Draw();
    glUseProgram(0);
}

void Renderer::Shutdown()
{
    m_mesh.Shutdown();
    if (m_shaderProgram != 0) glDeleteProgram(m_shaderProgram);
    m_shaderProgram = 0;
}
