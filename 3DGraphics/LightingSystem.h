#pragma once
#include <glm/glm.hpp>
#include "Shader.h" 

class LightingSystem {
    glm::vec3 pointLightPos;

    // В будущем можно добавить структуры DirLightData, PointLightData и т.д.
    // Пока храним просто константы для Phong Model
    glm::vec3 dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);

    static constexpr float POINT_LIGHT_CONSTANT = 1.0f;
    static constexpr float POINT_LIGHT_LINEAR = 0.09f;
    static constexpr float POINT_LIGHT_QUADRATIC = 0.032f;
public:

    LightingSystem(glm::vec3 initialPos) : pointLightPos(initialPos) {}

    void Update(float gameTime);

    void ApplyUniforms(Shader& shader, const glm::vec3& viewPos) const;

    const glm::vec3& GetLightPos() const { return pointLightPos; }
};