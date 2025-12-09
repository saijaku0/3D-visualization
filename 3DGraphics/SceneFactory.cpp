#include "SceneFactory.h"
#include "Core/GameObject.h"
#include "Core/Transform.h"
#include "Core/ResourceManager.h"

#include "Graphics/MeshRendererComponent.h"
#include "Physics/RigidbodyComponent.h"
#include "Physics/BoxColliderComponent.h"
#include "Physics/PhysicsWorld.h"

void SceneFactory::LoadDefaultScene(std::vector<std::unique_ptr<GameObject>>& objects, PhysicsWorld* physicsWorld) {

    // --- Пол ---
    objects.push_back(CreateBox(
        "cube",
        glm::vec3(0.0f, -2.0f, 0.0f),
        glm::vec3(30.0f, 1.0f, 30.0f),
        glm::vec3(0.0f),
        true, // Статичный
        physicsWorld
    ));

    // --- Стены ---
    // Задняя
    objects.push_back(CreateBox(
        "cube",
        glm::vec3(0.0f, 0.5f, -15.0f),
        glm::vec3(30.0f, 5.0f, 1.0f),
        glm::vec3(0.0f),
        true,
        physicsWorld
    ));

    // Передняя
    objects.push_back(CreateBox(
        "cube",
        glm::vec3(0.0f, 0.5f, 15.0f),
        glm::vec3(30.0f, 5.0f, 1.0f),
        glm::vec3(0.0f),
        true,
        physicsWorld
    ));

    // Левая
    objects.push_back(CreateBox(
        "cube",
        glm::vec3(-15.0f, 0.5f, 0.0f),
        glm::vec3(1.0f, 5.0f, 30.0f),
        glm::vec3(0.0f),
        true,
        physicsWorld
    ));

    // Правая
    objects.push_back(CreateBox(
        "cube",
        glm::vec3(15.0f, 0.5f, 0.0f),
        glm::vec3(1.0f, 5.0f, 30.0f),
        glm::vec3(0.0f),
        true,
        physicsWorld
    ));

    // Можно добавить случайные кубики
    objects.push_back(CreateBox(
        "cube",
        glm::vec3(5.0f, 5.0f, 5.0f), 
        glm::vec3(1.0f),
        glm::vec3(45.0f, 45.0f, 0.0f),
        false, 
        physicsWorld
    ));
}

std::unique_ptr<GameObject> SceneFactory::CreateBox(
    const std::string& meshName,
    glm::vec3 pos,
    glm::vec3 scale,
    glm::vec3 rotation,
    bool isStatic,
    PhysicsWorld* physicsWorld)
{
    auto obj = std::make_unique<GameObject>();
    Transform* t = obj->GetTransformPtr();

    t->SetPosition(pos);
    t->SetScale(scale);

    auto render = std::make_unique<MeshRendererComponent>(obj.get());
    render->mesh = ResourceManager::GetMesh(meshName);
    obj->AddComponent(std::move(render));

    auto rb = std::make_unique<RigidbodyComponent>(obj.get());
    rb->isStatic = isStatic;
    rb->mass = isStatic ? 0.0f : 1.0f;

    if (physicsWorld) {
        physicsWorld->AddBody(rb.get());
    }

    obj->AddComponent(std::move(rb));

    auto col = std::make_unique<BoxColliderComponent>(obj.get());
    col->GetSize() = scale;
    obj->AddComponent(std::move(col));

    return obj;
}