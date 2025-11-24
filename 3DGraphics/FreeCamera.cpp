#include "FreeCamera.h"

FreeCamera::FreeCamera(glm::vec3 startPos) {
    GetPosition() = startPos;
    updateCameraVectors();
}

void FreeCamera::ProcessMovement(MovementDirection direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    switch (direction) {
    case MOVE_FORWARD:
        GetPosition() += GetFront() * velocity;
        break;

    case MOVE_BACKWARD:
        GetPosition() -= GetFront() * velocity;
        break;

    case MOVE_LEFT:
        GetPosition() -= GetRight() * velocity;
        break;

    case MOVE_RIGHT:
        GetPosition() += GetRight() * velocity;
        break;

    case MOVE_JUMP:
        GetPosition() += GetWorldUp() * velocity;
        break;

    default:
        break;
    }
}