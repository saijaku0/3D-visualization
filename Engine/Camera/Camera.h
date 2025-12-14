#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement {
    Forward, Backward, Left, Right, Up, Down
};

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f, float pitch = 0.0f);

    virtual ~Camera() = default;

    const glm::vec3& GetPosition() const { return m_Position; }
    const glm::vec3& GetFront() const { return m_Front; }
    const glm::vec3& GetRight() const { return m_Right; }
    const glm::vec3& GetUp() const { return m_Up; }
    const glm::vec3& GetWorldUp() const { return m_WorldUp; }

    void SetPosition(const glm::vec3& newPos) {
        m_Position = newPos;
    }

    void SetRotation(float yaw, float pitch) {
        m_Yaw = yaw;
        m_Pitch = pitch;
        updateCameraVectors();
    }

    void SetAspectRatio(float width, float height) {
        if (height == 0) height = 1; 
        AspectRatio = width / height;
    }

    float GetYaw() const { return m_Yaw; }
    float GetPitch() const { return m_Pitch; }
    float GetZoom() const { return m_Zoom; }

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    virtual void ProcessKeyboard(CameraMovement direction, float deltaTime);
    virtual void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    virtual void Update(float deltaTime);
    virtual void ProcessMouseScroll(float yoffset);

protected:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    float m_Yaw;
    float m_Pitch;

    float m_MovementSpeed;
    float m_MouseSensitivity;
    float m_Zoom;
    float m_zNear = 0.1f;
    float m_zFar = 100.0f;
    float AspectRatio = 1.777f;

    void updateCameraVectors();
};