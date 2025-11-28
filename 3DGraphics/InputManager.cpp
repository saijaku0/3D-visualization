#include "InputManager.h"
#define INPUT_MANAGER_H


void InputManager::BindKey(int glfwKey, MovementDirection direction) {
    keyToAction[glfwKey] = new MoveCommand(direction);
}

void InputManager::HandleInput(GLFWwindow* window, IMovable& target, float deltaTime) {
    for (auto const& [key, command] : keyToAction) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            command->Execute(target, deltaTime);
        }
    }
}

InputManager::~InputManager() {
    for (auto const& [key, command] : keyToAction) {
        delete command;
    }
}