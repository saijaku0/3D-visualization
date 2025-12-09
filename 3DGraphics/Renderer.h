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
    unsigned int depthMapFBO;
    unsigned int depthMap;
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

public:
    Renderer() : depthMapFBO(0.0f), depthMap(0.0f) {}

    void Clear();

    void InitShadow();

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
    glm::mat4 GetLightSpaceMatrix(const glm::vec3& lightDir);

    void RenderGameObjects(
        Shader& shader,
        const std::vector<std::unique_ptr<GameObject>>& gameObjects
    );
};