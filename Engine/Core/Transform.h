#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 m_scale = glm::vec3(1.0f);
    
    mutable glm::mat4 m_cachedModelMatrix;
    mutable bool m_isDirt = true;

public:
    glm::mat4 GetModelMatrix() const;

    const glm::vec3& GetPosition() const;
    const glm::quat& GetRotation() const;
    const glm::vec3& GetScale() const;

    void Translate(const glm::vec3& delta);
    void SetPosition(const glm::vec3& pos);
    void SetRotation(const glm::quat& rot);
    void SetScale(const glm::vec3& scale);
};

