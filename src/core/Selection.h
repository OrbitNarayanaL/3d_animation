#pragma once

#include <glm/glm.hpp>

struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;
};

bool RayTriangleIntersect(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t, float& u, float& v);
