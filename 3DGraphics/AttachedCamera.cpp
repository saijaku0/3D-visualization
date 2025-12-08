#include "AttachedCamera.h"

void AttachedCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;

    if (constrainPitch) {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }
}

void AttachedCamera::Update(float deltaTime) {
    if (!target) return;

    const Transform* targetTransform = target->GetTransformPtr();
    glm::vec3 targetPos = targetTransform->GetPosition();

    glm::vec3 lookAtTarget = targetPos + glm::vec3(0.0f, 1.5f, 0.0f);

    float horizDist = m_distance * cos(glm::radians(m_Pitch));
    float vertDist = m_distance * sin(glm::radians(m_Pitch));

    float theta = glm::radians(m_Yaw);

    float offsetX = horizDist * cos(theta);
    float offsetZ = horizDist * sin(theta);
    
    m_Position.x = lookAtTarget.x - offsetX;
    m_Position.z = lookAtTarget.z - offsetZ;
    m_Position.y = lookAtTarget.y - vertDist;

    m_Front = glm::normalize(lookAtTarget - m_Position);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}