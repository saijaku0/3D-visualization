#pragma once
#include "Camera.h"
#include "LightingSystem.h"

class Renderer {
public:
    Renderer() {}

    void Clear();

    void DrawScene(Shader& shader,
        Camera* activeCamera,
        LightingSystem& lightingSystem,
        const std::vector<GameObject>& gameObjects,
        Mesh* cubeGizmoMesh,
        float gameTime,
        int scrWidth, int scrHeight);

private:
    void DrawGizmos(Shader& shader, LightingSystem& lightingSystem, Mesh* cubeGizmoMesh);
};