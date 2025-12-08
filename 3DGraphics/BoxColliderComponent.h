#pragma once
#include "ColliderComponent.h"
#include "GameObject.h"

class BoxColliderComponent :
    public ColliderComponent {
    glm::vec3 halfExtents;
    glm::vec3 size = glm::vec3(1.0f);
public:

    BoxColliderComponent(GameObject* owner) : ColliderComponent(owner), halfExtents(0.5f) {}
    virtual ~BoxColliderComponent() = default;

    glm::vec3 GetWorldSize() const;

    void SetSize(const glm::vec3& fullSize);

    glm::vec3 GetSize() const;

    ColliderType GetColliderType() const override {
        return ColliderType::Box;
    }
};

