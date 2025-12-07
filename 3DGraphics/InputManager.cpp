#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window) : m_window(window) {
    BindKey(GLFW_KEY_W, GameAction::MoveForward);
    BindKey(GLFW_KEY_S, GameAction::MoveBackward);
    BindKey(GLFW_KEY_A, GameAction::MoveLeft);
    BindKey(GLFW_KEY_D, GameAction::MoveRight);
    BindKey(GLFW_KEY_SPACE, GameAction::Jump);
    BindKey(GLFW_KEY_LEFT_SHIFT, GameAction::Sprint);
}

void InputManager::BindKey(int glfwKey, GameAction action) {
    keyBindings[glfwKey] = action;
}

bool InputManager::GetButton(GameAction action) const {
    for (auto const& [key, act] : keyBindings) {
        if (act == action) {
            if (glfwGetKey(m_window, key) == GLFW_PRESS)
                return true;
        }
    }
    return false;
}

bool InputManager::GetButtonDown(GameAction action) const {
    return GetButton(action);
}