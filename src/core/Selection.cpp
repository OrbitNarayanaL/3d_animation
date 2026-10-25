#include "Selection.h"
#include <glm/glm.hpp>

bool RayTriangleIntersect(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t, float& u, float& v)
{
    const float EPSILON = 0.0000001f;
    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    glm::vec3 h = glm::cross(ray.direction, edge2);
    float a = glm::dot(edge1, h);
    if (a > -EPSILON && a < EPSILON)
        return false;
    float f = 1.0f / a;
    glm::vec3 s = ray.origin - v0;
    float uParam = f * glm::dot(s, h);
    if (uParam < 0.0f || uParam > 1.0f)
        return false;
    glm::vec3 q = glm::cross(s, edge1);
    float vParam = f * glm::dot(ray.direction, q);
    if (vParam < 0.0f || uParam + vParam > 1.0f)
        return false;
    float tParam = f * glm::dot(edge2, q);
    if (tParam > EPSILON)
    {
        t = tParam;
        u = uParam;
        v = vParam;
        return true;
    }
    return false;
}
