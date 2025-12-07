#include "SphereColliderComponent.h"

float SphereColliderComponent::GetWorldRadius() const {
    glm::vec3 scale = GetOwner()->GetTransformPtr()->GetScale();

    float maxScale = std::max({ scale.x, scale.y, scale.z });

    return radius * maxScale;
}