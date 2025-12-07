#include "Player.h"
#include "ResourceManager.h"
#include "MeshRendererComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "PlayerControllerComponent.h"
#include <iostream>
#include <cmath>

Player::Player(InputManager* input, Camera* camera) : GameObject() {
    GetTransformPtr()->SetPosition(glm::vec3(0, 2, 0));
    GetTransformPtr()->SetScale(glm::vec3(1.0f));

    auto meshRenderer = std::make_unique<MeshRendererComponent>(this);
    meshRenderer->mesh = ResourceManager::GetMesh("cube");
    AddComponent(std::move(meshRenderer));

    auto rb = std::make_unique<RigidbodyComponent>(this);
    rb->mass = 80.0f;
    rb->drag = 0.1f; 
    rb->useGravity = true;
    rb->isStatic = false;
    AddComponent(std::move(rb));

    auto collider = std::make_unique<BoxColliderComponent>(this);
    collider->size = glm::vec3(0.5f, 1.8f, 0.5f);
    AddComponent(std::move(collider));

    auto controller = std::make_unique<PlayerControllerComponent>(this, input, camera);
    AddComponent(std::move(controller));
}