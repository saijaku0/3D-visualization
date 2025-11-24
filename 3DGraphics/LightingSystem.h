#pragma once
#include <glm/glm.hpp>
#include "Shader.h" 

class LightingSystem {
private:
    glm::vec3 pointLightPos;

    // В будущем можно добавить структуры DirLightData, PointLightData и т.д.
    // Пока храним просто константы для Phong Model
    glm::vec3 dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);

    static constexpr float POINT_LIGHT_CONSTANT = 1.0f;
    static constexpr float POINT_LIGHT_LINEAR = 0.09f;
    static constexpr float POINT_LIGHT_QUADRATIC = 0.032f;
public:

    LightingSystem(glm::vec3 initialPos) : pointLightPos(initialPos) {}

    void Update(float gameTime) {
        float lightX = sin(gameTime) * 2.0f;
        float lightZ = cos(gameTime) * 2.0f;
        pointLightPos = glm::vec3(lightX, 1.0f, lightZ);
    }

    void ApplyUniforms(Shader& shader, const glm::vec3& viewPos) const {
        shader.setVec3("dirLight.direction", dirLightDirection);
        shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

        shader.setVec3("pointLight.position", pointLightPos);
        shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLight.diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLight.constant", POINT_LIGHT_CONSTANT);
        shader.setFloat("pointLight.linear", POINT_LIGHT_LINEAR);
        shader.setFloat("pointLight.quadratic", POINT_LIGHT_QUADRATIC);

        shader.setVec3("viewPos", viewPos);
    }

    const glm::vec3& GetLightPos() const { return pointLightPos; }
};