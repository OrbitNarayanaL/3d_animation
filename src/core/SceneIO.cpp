#include "SceneIO.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool SceneIO::SaveScene(const std::string& filePath, float roughness, float metalness, const float albedo[3])
{
    std::ofstream file(filePath);
    if (!file.is_open())
        return false;
    file << "[SCENE]" << std::endl;
    file << "roughness=" << roughness << std::endl;
    file << "metalness=" << metalness << std::endl;
    file << "albedo_r=" << albedo[0] << std::endl;
    file << "albedo_g=" << albedo[1] << std::endl;
    file << "albedo_b=" << albedo[2] << std::endl;
    file.close();
    return true;
}

bool SceneIO::LoadScene(const std::string& filePath, float& roughness, float& metalness, float albedo[3])
{
    std::ifstream file(filePath);
    if (!file.is_open())
        return false;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.find("roughness=") == 0)
        {
            std::string val = line.substr(10);
            roughness = std::stof(val);
        }
        else if (line.find("metalness=") == 0)
        {
            std::string val = line.substr(10);
            metalness = std::stof(val);
        }
        else if (line.find("albedo_r=") == 0)
        {
            std::string val = line.substr(9);
            albedo[0] = std::stof(val);
        }
        else if (line.find("albedo_g=") == 0)
        {
            std::string val = line.substr(9);
            albedo[1] = std::stof(val);
        }
        else if (line.find("albedo_b=") == 0)
        {
            std::string val = line.substr(9);
            albedo[2] = std::stof(val);
        }
    }
    file.close();
    return true;
}

bool SceneIO::ExportMeshToOBJ(const std::string& filePath, const Mesh& mesh)
{
    std::ofstream file(filePath);
    if (!file.is_open())
        return false;
    file << "# Exported by 3D Character Creation Software" << std::endl;
    for (const auto& v : mesh.vertices)
    {
        file << "v " << v.position.x << " " << v.position.y << " " << v.position.z << std::endl;
    }
    for (const auto& v : mesh.vertices)
    {
        file << "vt " << v.texCoords.x << " " << v.texCoords.y << std::endl;
    }
    for (const auto& v : mesh.vertices)
    {
        file << "vn " << v.normal.x << " " << v.normal.y << " " << v.normal.z << std::endl;
    }
    for (size_t i = 0; i < mesh.indices.size(); i += 3)
    {
        unsigned int i1 = mesh.indices[i] + 1;
        unsigned int i2 = mesh.indices[i + 1] + 1;
        unsigned int i3 = mesh.indices[i + 2] + 1;
        file << "f " << i1 << "/" << i1 << "/" << i1 << " " << i2 << "/" << i2 << "/" << i2 << " " << i3 << "/" << i3 << "/" << i3 << std::endl;
    }
    file.close();
    return true;
}
