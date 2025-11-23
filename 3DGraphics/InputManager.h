#pragma once
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <map>
#include "Command.h"
#include "IMoveAble.h"

class InputManager {
private:
    std::map<int, Command*> keyToAction;

public:
    InputManager() = default;

    void BindKey(int glfwKey, MovementDirection direction);

    void HandleInput(GLFWwindow* window, IMovable& target, float deltaTime);

    ~InputManager();
};

#endif