#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "IMoveAble.h"

class Camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float zoom;
    float mouseSensitivity;
public:

    Camera() :
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        position(0.0f, 0.0f, 0.0f),
        up(0.0f, 0.0f, 0.0f),
        right(0.0f, 0.0f, 0.0f),
        movementSpeed(2.5f),
        mouseSensitivity(0.1f),
        zoom(45.0f),
        worldUp(0.0f, 1.0f, 0.0f),
        yaw(-90.0f), pitch(0.0f) 
    { }

    virtual ~Camera() {} 

    glm::vec3& GetPosition() { return position; }
    glm::vec3& GetWorldUp() { return worldUp; }
    glm::vec3& GetFront() { return front; }
    glm::vec3& GetRight() { return right; }
    const glm::vec3& GetPosition() const { return position; }
    const glm::vec3& GetFront() const { return front; }
    float& GetYaw() { return yaw; }
    float& GetPitch() { return pitch; }
    float& GetZoom() { return zoom; }
    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }
    glm::mat4 GetProjectionMatrix(float aspectRatio) const {
        return glm::perspective(glm::radians(zoom), aspectRatio, 0.1f, 100.0f);
    }

    virtual void Update(float deltaTime) = 0;
    virtual void ProcessKeyboard(MovementDirection direction, float deltaTime) {} 
    virtual void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

protected:
    float movementSpeed;

    void updateCameraVectors();
};

#endif