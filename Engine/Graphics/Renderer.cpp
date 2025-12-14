#include "Renderer.h"
#include "../Core/ResourceManager.h"

#include <glm/glm.hpp>

void Renderer::InitShadow() {
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

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
    glDisable(GL_CULL_FACE);
    GLint currentFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);

    glm::mat4 lightSpaceMatrix = GetLightSpaceMatrix(lightingSystem.dirLight.direction);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glClear(GL_DEPTH_BUFFER_BIT);

    auto depthShader = ResourceManager::GetShader("shadow_depth");
    depthShader->use();
    depthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    RenderGameObjects(*depthShader, gameObjects);

    glBindFramebuffer(GL_FRAMEBUFFER, currentFBO);
    glViewport(0, 0, scrWidth, scrHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    shader.setInt("shadowMap", 1);

    if (scrHeight == 0 || scrWidth == 0) return;

    glm::mat4 projection = glm::perspective(glm::radians(activeCamera->GetZoom()), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
    glm::mat4 view = activeCamera->GetViewMatrix();

    shader.set("projection", projection);
    shader.set("view", view);
    shader.setVec3("viewPos", activeCamera->GetPosition());

    lightingSystem.ApplyUniforms(shader);

    for (const auto& obj : gameObjects) {
        auto meshRenderer = obj->GetComponent<MeshRendererComponent>();

        if(!meshRenderer || !meshRenderer->GetMesh()) continue;

        Transform* transform = obj->GetTransformPtr();

        if (transform) {
            glm::mat4 model = transform->GetModelMatrix();
            shader.setMat4("model", model);
            
        }

        glBindVertexArray(meshRenderer->GetMesh()->GetVAO());

        shader.setVec3("objectColor", meshRenderer->color);

        meshRenderer->GetMesh()->Draw(shader);
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

glm::mat4 Renderer::GetLightSpaceMatrix(const glm::vec3& lightDir) {
    float near_plane = 1.0f, far_plane = 50.0f;
    glm::mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
    glm::vec3 lightPos = glm::vec3(0.0f) - glm::normalize(lightDir) * 20.0f;
    glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    return lightProjection * lightView;
}

void Renderer::RenderGameObjects(Shader& shader, const std::vector<std::unique_ptr<GameObject>>& gameObjects) {
    for (const auto& obj : gameObjects) {
        auto mr = obj->GetComponent<MeshRendererComponent>();
        if (!mr || !mr->GetMesh()) continue;

        Transform* tr = obj->GetTransformPtr();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, tr->GetPosition());
        model *= glm::mat4_cast(tr->GetRotation());
        model = glm::scale(model, tr->GetScale());

        shader.setMat4("model", model);

        mr->GetMesh()->Draw(shader);
    }
}