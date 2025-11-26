#include "Renderer.h"

void Renderer::Clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawScene(Shader& shader,
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

    shader.set("projection", projection);
    shader.set("view", view);

    lightingSystem.ApplyUniforms(shader, activeCamera->GetPosition());

    for (auto& obj : gameObjects) {
        obj.draw(shader, gameTime);
    }

    DrawGizmos(shader, lightingSystem, cubeGizmoMesh);
}

/*
* Private
*/

void Renderer::DrawGizmos(Shader& shader, LightingSystem& lightingSystem, Mesh* cubeGizmoMesh) {
    shader.setVec3("pointLight.ambient", 1.0f, 1.0f, 1.0f);

    GameObject gizmoLamp;
    gizmoLamp.position = lightingSystem.GetLightPos();
    gizmoLamp.scale = glm::vec3(0.2f);
    gizmoLamp.color = glm::vec3(1.0f, 1.0f, 0.0f);
    gizmoLamp.mesh = cubeGizmoMesh;
    gizmoLamp.draw(shader, 0);

    shader.setVec3("pointLight.ambient", 0.05f, 0.05f, 0.05f);
}