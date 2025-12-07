#include "BoxColliderComponent.h"

glm::vec3 BoxColliderComponent::GetWorldSize() const {
    glm::vec3 worldScale = GetOwner()->GetTransformPtr()->GetScale();
    return size * worldScale;
}