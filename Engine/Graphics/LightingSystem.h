#pragma once
#include <glm/glm.hpp>
#include "Shader.h" 

struct PointLight {
    glm::vec3 position;

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    glm::vec3 ambient = glm::vec3(0.05f);
    glm::vec3 diffuse = glm::vec3(0.8f);
    glm::vec3 specular = glm::vec3(1.0f);
};

struct DirLight {
    glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);

    glm::vec3 ambient = glm::vec3(0.05f);
    glm::vec3 diffuse = glm::vec3(0.4f);
    glm::vec3 specular = glm::vec3(0.5f);
};

class LightingSystem {
public:
    DirLight dirLight;
    std::vector<PointLight> pointLights;

    LightingSystem() = default;

    void AddPointLight(const glm::vec3& pos, const glm::vec3& color = glm::vec3(1.0f));

    void ApplyUniforms(Shader& shader) const;
};