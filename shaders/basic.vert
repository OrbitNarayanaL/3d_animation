#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec4 aBoneIds;
layout (location = 4) in vec4 aBoneWeights;

uniform mat4 uBoneTransforms[100];

out vec2 vTexCoords;

void main()
{
    mat4 boneTransform = mat4(1.0);
    if (aBoneWeights.x > 0.0 && aBoneIds.x >= 0 && aBoneIds.x < 100)
        boneTransform += uBoneTransforms[aBoneIds.x] * aBoneWeights.x;
    if (aBoneWeights.y > 0.0 && aBoneIds.y >= 0 && aBoneIds.y < 100)
        boneTransform += uBoneTransforms[aBoneIds.y] * aBoneWeights.y;
    if (aBoneWeights.z > 0.0 && aBoneIds.z >= 0 && aBoneIds.z < 100)
        boneTransform += uBoneTransforms[aBoneIds.z] * aBoneWeights.z;
    if (aBoneWeights.w > 0.0 && aBoneIds.w >= 0 && aBoneIds.w < 100)
        boneTransform += uBoneTransforms[aBoneIds.w] * aBoneWeights.w;
    if (aBoneWeights.x == 0.0 && aBoneWeights.y == 0.0 && aBoneWeights.z == 0.0 && aBoneWeights.w == 0.0)
        boneTransform = mat4(1.0);
    vTexCoords = aTexCoords;
    gl_Position = boneTransform * vec4(aPos, 1.0);
}
