#include "GameManager.h"

GameManager::GameManager(int width, int height) :
    isGameMode(false),
    firstMouse(true),
    escKeyPressed(false),
    lastX(static_cast<float>(width) / 2.0f),
    lastY(static_cast<float>(height) / 2.0f)
{ }

bool GameManager::IsMouseRotationActive(GLFWwindow* window) {
    if (isGameMode) return true;

    bool rightClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

    if (rightClick) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        return true;
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse = true;
        return false;
    }
}

void GameManager::switchToGameMode(GLFWwindow* window, FreeCamera* devCam, AttachedCamera* playerCam, Player* playerObj, Camera** activeCamPtr, IMovable** currentControllerPtr) {
    if (isGameMode) return;

    isGameMode = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    playerCam->yaw = devCam->yaw;
    playerCam->pitch = devCam->pitch;
    playerCam->ProcessMouseMovement(0, 0);

    *activeCamPtr = playerCam;
    *currentControllerPtr = playerObj;

    firstMouse = true;
    std::cout << "GAME MODE" << std::endl;
}

void GameManager::switchToDeveloperMode(GLFWwindow* window, FreeCamera* devCam, AttachedCamera* playerCam, Player* playerObj, Camera** activeCamPtr, IMovable** currentControllerPtr) {
    if (!isGameMode) return;

    isGameMode = false;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    devCam->position = playerObj->position - (playerObj->scale.z * 2.0f * playerCam->front) + glm::vec3(0, 2, 0);

    devCam->yaw = playerCam->yaw;
    devCam->pitch = playerCam->pitch;
    devCam->ProcessMouseMovement(0, 0);

    *activeCamPtr = devCam;
    *currentControllerPtr = devCam;

    std::cout << "DEVELOPER MODE" << std::endl;
}


void GameManager::ProcessModeSwitch(GLFWwindow* window, FreeCamera* devCam, AttachedCamera* playerCam, Player* playerObj, Camera** activeCamPtr, IMovable** currentControllerPtr) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        if (!escKeyPressed) {
            if (isGameMode) {
                switchToDeveloperMode(window, devCam, playerCam, playerObj, activeCamPtr, currentControllerPtr);
            }
            else {
                glfwSetWindowShouldClose(window, true);
            }
            escKeyPressed = true;
        }
    }
    else {
        escKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && !isGameMode) {
        switchToGameMode(window, devCam, playerCam, playerObj, activeCamPtr, currentControllerPtr);
    }
}