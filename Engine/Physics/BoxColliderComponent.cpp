#include "BoxColliderComponent.h"

void BoxColliderComponent::SetSize(const glm::vec3& fullSize) {
    size = fullSize * 0.5f;
}

glm::vec3 BoxColliderComponent::GetSize() const {
    return size;
}

glm::vec3 BoxColliderComponent::GetWorldSize() const {
    glm::vec3 worldScale = GetOwner()->GetTransformPtr()->GetScale();
    return size * worldScale;
}