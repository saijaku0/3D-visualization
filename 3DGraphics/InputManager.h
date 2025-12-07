#pragma once
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <glad/glad.h>
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
    Crouch, 
    Fire
};

class InputManager {
    std::map<int, GameAction> keyBindings;
    GLFWwindow* m_window;

public:
    InputManager(GLFWwindow* window);

    void BindKey(int glfwKey, GameAction action);

    bool GetButton(GameAction action) const;
    bool GetButtonDown(GameAction action) const;
};

#endif