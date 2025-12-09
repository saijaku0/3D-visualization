#include "DebugRenderer.h"
#include "../Core/ResourceManager.h" 
#include "../Physics/BoxColliderComponent.h"
#include "../Physics/SphereColliderComponent.h" 

std::shared_ptr<Shader> DebugRenderer::m_shader = nullptr;

void DebugRenderer::Init(std::shared_ptr<Shader> shader) {
    m_shader = shader;
}

void DebugRenderer::RenderColliders(
    const std::vector<std::unique_ptr<GameObject>>& objects,
    const Camera* camera)
{
    if (!m_shader) {
        std::cerr << "DebugRenderer not initialized!" << std::endl;
        return;
    }

    GLint polygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, polygonMode);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE); 

    m_shader->use();
    m_shader->setMat4("view", camera->GetViewMatrix());

    m_shader->setVec3("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));

    auto cubeMesh = ResourceManager::GetMesh("cube");

    for (const auto& obj : objects) {
        auto box = obj->GetComponent<BoxColliderComponent>();
        if (box) {
            Transform* tr = obj->GetTransformPtr();
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, tr->GetPosition() + box->centerOffset);
            model *= glm::mat4_cast(tr->GetRotation());

            glm::vec3 debugScale = box->GetSize() * 2.0f;

            model = glm::scale(model, debugScale);

            m_shader->setMat4("model", model);
            cubeMesh->Draw(*m_shader);
        }

        auto sphere = obj->GetComponent<SphereColliderComponent>();
        if (sphere) {
            Transform* tr = obj->GetTransformPtr();
            glm::mat4 model = glm::mat4(1.0f);

            model = glm::translate(model, tr->GetPosition() + sphere->centerOffset);

            model *= glm::mat4_cast(tr->GetRotation());

            float debugScale = sphere->radius * 2.0f;
            model = glm::scale(model, glm::vec3(debugScale));

            m_shader->setMat4("model", model);
            ResourceManager::GetMesh("sphere")->Draw(*m_shader);
        }
    }

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode[0]);
    glEnable(GL_CULL_FACE);
}