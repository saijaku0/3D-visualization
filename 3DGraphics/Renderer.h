#pragma once
#include <memory> 
#include <vector>

#include "Camera.h"
#include "LightingSystem.h"
#include "MeshRendererComponent.h"
#include "Shader.h"
#include "GameObject.h"
#include "Mesh.h"

class Renderer {
public:
    Renderer() {}

    void Clear();

    void DrawScene(
        Shader& shader,
        Camera* activeCamera,
        LightingSystem& lightingSystem,
        const std::vector<std::unique_ptr<GameObject>>& gameObjects,
        std::shared_ptr<Mesh> cubeGizmoMesh,
        float gameTime,
        int scrWidth, int scrHeight);

    void DrawGizmos(
        Shader& shader, 
        const LightingSystem& lightingSystem,
        std::shared_ptr<Mesh> debugMesh
    );
private:
};