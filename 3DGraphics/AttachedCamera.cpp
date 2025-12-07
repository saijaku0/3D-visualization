#include "AttachedCamera.h"

void AttachedCamera::Update(float deltaTime) {
    if (!target) return;

    const Transform* targetTransform = target->GetTransformPtr();

    glm::vec3 rotatedOffset = targetTransform->GetRotation() * offset;
    m_Position = targetTransform->GetPosition() + rotatedOffset;

    glm::vec3 lookTarget = targetTransform->GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f);

    m_Front = glm::normalize(lookTarget - m_Position);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}