#pragma once
#ifndef IMOVABLE_H
#define IMOVABLE_H

enum MovementDirection {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_JUMP
};

class IMovable {
public:
    virtual ~IMovable() {}

    virtual void ProcessMovement(MovementDirection direction, float deltaTime) = 0;
};

#endif