#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Joint
{
    std::string name;
    int index;
    int parentIndex;
    glm::mat4 localTransform;
    glm::mat4 inverseBindTransform;
    glm::mat4 globalTransform;
};

class Skeleton
{
public:
    std::vector<Joint> joints;

    Skeleton();
    ~Skeleton();

    void UpdateJointTransforms(int jointIndex = 0, const glm::mat4& parentTransform = glm::mat4(1.0f));
    void AddJoint(const std::string& name, int parentIndex, const glm::mat4& localTransform);
};
