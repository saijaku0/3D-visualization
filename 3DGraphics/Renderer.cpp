#include "Renderer.h"

#include <glm/glm.hpp>

void Renderer::Clear() {
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawScene(Shader& shader,
    Camera* activeCamera,
    LightingSystem& lightingSystem,
    const std::vector<std::unique_ptr<GameObject>>& gameObjects,
    std::shared_ptr<Mesh> cubeGizmoMesh,
    float gameTime,
    int scrWidth, int scrHeight)
{
    shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(activeCamera->GetZoom()), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
    glm::mat4 view = activeCamera->GetViewMatrix();

    shader.set("projection", projection);
    shader.set("view", view);
    shader.setVec3("viewPos", activeCamera->GetPosition());

    lightingSystem.ApplyUniforms(shader);

    for (const auto& obj : gameObjects) {
        auto meshRenderer = obj->GetComponent<MeshRendererComponent>();

        if(!meshRenderer || !meshRenderer->mesh) continue;

        Transform* transform = obj->GetTransformPtr();

        if (transform) {
            glm::mat4 model = transform->GetModelMatrix();
            shader.setMat4("model", model);
        }

        shader.setVec3("objectColor", meshRenderer->color);

        meshRenderer->mesh->Draw(shader);
    }

    DrawGizmos(shader, lightingSystem, cubeGizmoMesh);
}

void Renderer::DrawGizmos(Shader& shader, const LightingSystem& lightingSystem, std::shared_ptr<Mesh> debugMesh) {
    if (!debugMesh) return;

    for (const auto& light : lightingSystem.pointLights) {

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, light.position);

        model = glm::scale(model, glm::vec3(0.2f));

        shader.setMat4("model", model);

        shader.setVec3("objectColor", light.diffuse);

        debugMesh->Draw(shader);
    }
}