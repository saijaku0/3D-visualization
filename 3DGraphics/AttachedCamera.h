#pragma once
#ifndef ATTACHEDCAMERA_H
#define ATTACHEDCAMERA_H

#include "Camera.h"
#include "GameObject.h"

class AttachedCamera : public Camera {
    const GameObject* target;
    glm::vec3 offset;
public:
    AttachedCamera(GameObject* targetObj, glm::vec3 offsetVal = glm::vec3(0.0f, 0.8f, 0.0f))
        : target(targetObj), offset(offsetVal)
    {
        Update(0.0f);
    }

    void Update(float deltaTime) override;

    void SetTarget(const GameObject* newTarget) { target = newTarget; }
};

#endif // !ATTACHEDCAMERA_H