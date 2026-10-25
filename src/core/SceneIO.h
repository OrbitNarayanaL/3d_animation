#pragma once

#include <string>
#include "Mesh.h"

class SceneIO
{
public:
    static bool SaveScene(const std::string& filePath, float roughness, float metalness, const float albedo[3]);
    static bool LoadScene(const std::string& filePath, float& roughness, float& metalness, float albedo[3]);
    static bool ExportMeshToOBJ(const std::string& filePath, const Mesh& mesh);
};
