#pragma once
#include "ColliderComponent.h"
#include "GameObject.h"
#include <algorithm>

class SphereColliderComponent :
    public ColliderComponent {
public:
    float radius = 0.5f; 

    SphereColliderComponent(GameObject* owner) : ColliderComponent(owner) {}
    virtual ~SphereColliderComponent() = default;

    ColliderType GetColliderType() const override { return ColliderType::Sphere; }

    float GetWorldRadius() const;
};

