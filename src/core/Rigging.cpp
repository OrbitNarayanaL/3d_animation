#include "Rigging.h"

Skeleton::Skeleton()
{
}

Skeleton::~Skeleton()
{
}

void Skeleton::AddJoint(const std::string& name, int parentIndex, const glm::mat4& localTransform)
{
    Joint joint;
    joint.name = name;
    joint.index = (int)joints.size();
    joint.parentIndex = parentIndex;
    joint.localTransform = localTransform;
    joint.inverseBindTransform = glm::mat4(1.0f);
    joint.globalTransform = glm::mat4(1.0f);
    joints.push_back(joint);
}

void Skeleton::UpdateJointTransforms(int jointIndex, const glm::mat4& parentTransform)
{
    if (jointIndex < 0 || jointIndex >= (int)joints.size()) return;
    joints[jointIndex].globalTransform = parentTransform * joints[jointIndex].localTransform;
    for (size_t i = 0; i < joints.size(); ++i)
    {
        if (joints[i].parentIndex == jointIndex && (int)i != jointIndex)
        {
            UpdateJointTransforms((int)i, joints[jointIndex].globalTransform);
        }
    }
}
