#include "InputManager.h"

InputManager::InputManager() {
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

bool InputManager::IsActionActive(GLFWwindow* window, GameAction action) const {

    for (const auto& [key, bindingAction] : keyBindings) {
        if (bindingAction == action) {
            if (glfwGetKey(window, key) == GLFW_PRESS) {
                return true; 
            }
        }
    }
    return false;
}