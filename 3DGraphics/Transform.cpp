#include "Transform.h"

glm::mat4 Transform::GetModelMatrix() const {
    if (!m_isDirt)
        return m_cachedModelMatrix;

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, m_position);
    model *= glm::mat4_cast(m_rotation);
    model = glm::scale(model, m_scale);

    m_isDirt = false;
    m_cachedModelMatrix = model;

    return model;
}

const glm::vec3& Transform::GetPosition() const { return m_position; }

const glm::quat& Transform::GetRotation() const { return m_rotation; }

const glm::vec3& Transform::GetScale() const { return m_scale; }

void Transform::Translate(const glm::vec3& delta) { 
    m_position += delta; 
    m_isDirt = true;
}

void Transform::SetPosition(const glm::vec3& pos) { 
    m_position = pos;  
    m_isDirt = true;
}

void Transform::SetRotation(const glm::quat& rot) { 
    m_rotation = rot; 
    m_isDirt = true;
}

void Transform::SetScale(const glm::vec3& scale) { 
    m_scale = scale; 
    m_isDirt = true;
}