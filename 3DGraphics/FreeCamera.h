#pragma once
#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "Camera.h"
#include "IMoveAble.h"

class FreeCamera : public Camera, public IMovable {
public:
    FreeCamera(glm::vec3 startPos);

    void ProcessMovement(MovementDirection direction, float deltaTime) override;

    void Update(float deltaTime) override { }
};

#endif // !FREECAMERA_H