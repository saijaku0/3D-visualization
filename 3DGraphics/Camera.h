#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "IMoveAble.h"

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float zoom;
    float mouseSensitivity;

    Camera() :
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed(2.5f),
        mouseSensitivity(0.1f),
        zoom(45.0f),
        worldUp(0.0f, 1.0f, 0.0f),
        yaw(-90.0f), pitch(0.0f)
    {
    }

    virtual ~Camera() {} 

    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 GetProjectionMatrix(float aspectRatio) const {
        return glm::perspective(glm::radians(zoom), aspectRatio, 0.1f, 100.0f);
    }

    virtual void Update(float deltaTime) = 0;
    virtual void ProcessKeyboard(MovementDirection direction, float deltaTime) {} // По умолчанию ничего не делает

    virtual void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (constrainPitch) {
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }
        updateCameraVectors();
    }

protected:
    float movementSpeed;

    void updateCameraVectors() {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};

class FreeCamera : public Camera, public IMovable {
public:
    FreeCamera(glm::vec3 startPos) {
        position = startPos;
        updateCameraVectors();
    }

    // Реализуем метод интерфейса
    void ProcessMovement(MovementDirection direction, float deltaTime) override {
        float velocity = movementSpeed * deltaTime;

        if (direction == MOVE_FORWARD)  position += front * velocity;
        if (direction == MOVE_BACKWARD) position -= front * velocity;
        if (direction == MOVE_LEFT)     position -= right * velocity;
        if (direction == MOVE_RIGHT)    position += right * velocity;
        // JUMP для свободной камеры - это полет вверх (опционально)
        if (direction == MOVE_JUMP)     position += worldUp * velocity;
    }

    void Update(float deltaTime) override {
    }
};

class AttachedCamera : public Camera {
    GameObject* target; 
    glm::vec3 offset;   

public:
    AttachedCamera(GameObject* targetObj, glm::vec3 offsetVal = glm::vec3(0.0f, 0.8f, 0.0f))
        : target(targetObj), offset(offsetVal)
    {
        updateCameraVectors();
    }

    void ProcessKeyboard(MovementDirection direction, float deltaTime) override {}

    void Update(float deltaTime) override {
        if (target) {
            position = target->position + offset;
        }
    }
};

#endif