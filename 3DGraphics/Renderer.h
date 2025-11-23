// Renderer.h
#pragma once
#include "Camera.h"
#include "LightingSystem.h"

class Renderer {
public:
    Renderer() {}

    void Clear() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void DrawScene(Shader& shader,
        Camera* activeCamera,
        LightingSystem& lightingSystem,
        const std::vector<GameObject>& gameObjects,
        Mesh* cubeGizmoMesh,
        float gameTime,
        int scrWidth, int scrHeight)
    {
        shader.use();

        if (scrHeight == 0) scrHeight = 1;
        float aspectRatio = (float)scrWidth / (float)scrHeight;

        glm::mat4 projection = activeCamera->GetProjectionMatrix(aspectRatio);
        glm::mat4 view = activeCamera->GetViewMatrix();

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        lightingSystem.ApplyUniforms(shader, activeCamera->position);

        for (auto& obj : gameObjects) {
            obj.draw(shader, gameTime);
        }

        DrawGizmos(shader, lightingSystem, cubeGizmoMesh);
    }

private:
    void DrawGizmos(Shader& shader, LightingSystem& lightingSystem, Mesh* cubeGizmoMesh) {
        shader.setVec3("pointLight.ambient", 1.0f, 1.0f, 1.0f);

        GameObject gizmoLamp;
        gizmoLamp.position = lightingSystem.GetLightPos();
        gizmoLamp.scale = glm::vec3(0.2f);
        gizmoLamp.color = glm::vec3(1.0f, 1.0f, 0.0f);
        gizmoLamp.mesh = cubeGizmoMesh;
        gizmoLamp.draw(shader, 0);

        shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
    }
};