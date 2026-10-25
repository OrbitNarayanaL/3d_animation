#version 330 core

out vec4 FragColor;

uniform vec3 uAlbedoColor;
uniform float uRoughness;
uniform float uMetalness;

void main()
{
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    vec3 normal = normalize(vec3(0.0, 0.0, 1.0));
    float NdotL = max(dot(normal, lightDir), 0.0);
    
    // Lambertian diffuse
    vec3 diffuse = uAlbedoColor * NdotL;
    
    // Simplified specular (Cook-Torrance approximation)
    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0));
    vec3 halfVec = normalize(lightDir + viewDir);
    float NdotH = max(dot(normal, halfVec), 0.0);
    float spec = pow(NdotH, max(1.0 - uRoughness, 0.01) * 128.0);
    vec3 specular = mix(vec3(0.04), uAlbedoColor, uMetalness) * spec * (1.0 - uRoughness);
    
    vec3 result = diffuse + specular;
    FragColor = vec4(result, 1.0);
}
