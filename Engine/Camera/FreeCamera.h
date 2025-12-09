#pragma once
#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "Camera.h"

class FreeCamera : public Camera {
public:
    FreeCamera(glm::vec3 startPos)
        : Camera(startPos) 
    {
        updateCameraVectors();
    }
    void ProcessKeyboard(CameraMovement direction, float deltaTime) override;
};

#endif // !FREECAMERA_H