#pragma once

#include "Camera.h"
#include "LightingSystem.h"
#include "Shader.h"
#include "GameObject.h"
#include "Mesh.h"
#include <memory> 
#include <vector>

class Renderer {
public:
    Renderer() {}

    void Clear();

    void DrawScene(Shader& shader,
        Camera* activeCamera,
        LightingSystem& lightingSystem,
        const std::vector<GameObject>& gameObjects,
        std::shared_ptr<Mesh> cubeGizmoMesh,
        float gameTime,
        int scrWidth, int scrHeight);

private:
    void DrawGizmos(Shader& shader, LightingSystem& lightingSystem, std::shared_ptr<Mesh> cubeGizmoMesh);
};