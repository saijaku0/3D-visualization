#pragma once
#include "../Core/Component.h"
#include <glm/glm.hpp>

enum class ColliderType {
    Box,
    Sphere,
    Capsule
};

class ColliderComponent :
    public Component {
public:
    float friction = 0.5f;
    float restitution = 0.0f;

    glm::vec3 centerOffset = glm::vec3(0.0f);
    
    ColliderComponent(GameObject* owner) : Component(owner) {}
    virtual ~ColliderComponent() = default;

    virtual ColliderType GetColliderType() const = 0;
};

