#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include "IMoveAble.h"

class Command {
public:
    virtual ~Command() = default;

    virtual void Execute(IMovable& target, float deltaTime) const = 0;
};

class MoveCommand : public Command {
private:
    MovementDirection direction;
public:
    MoveCommand(MovementDirection dir) : direction(dir) {}

    void Execute(IMovable& target, float deltaTime) const override {
        target.ProcessMovement(direction, deltaTime);
    }
};

#endif