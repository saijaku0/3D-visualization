#pragma once
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <map>
#include <vector>

enum class GameAction {
    MoveForward,
    MoveBackward,
    MoveLeft,
    MoveRight,
    Jump,
    Sprint,
    Crouch
};

class InputManager {
private:
    std::map<int, GameAction> keyBindings;

public:
    InputManager();

    void BindKey(int glfwKey, GameAction action);

    bool IsActionActive(GLFWwindow* window, GameAction action) const;
};

#endif