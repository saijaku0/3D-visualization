#pragma once
#include "ColliderComponent.h"
#include "GameObject.h"

class BoxColliderComponent :
    public ColliderComponent {
public:
    glm::vec3 size = glm::vec3(1.0f);

    BoxColliderComponent(GameObject* owner) : ColliderComponent(owner) {}
    virtual ~BoxColliderComponent() = default;

    glm::vec3 GetWorldSize() const;

    ColliderType GetColliderType() const override {
        return ColliderType::Box;
    }
};

