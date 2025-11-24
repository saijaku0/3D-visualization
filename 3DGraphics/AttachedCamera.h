#pragma once
#ifndef ATTACHEDCAMERA_H
#define ATTACHEDCAMERA_H

#include "Camera.h"

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
            GetPosition() = target->position + offset;
        }
    }
};

#endif // !ATTACHEDCAMERA_H