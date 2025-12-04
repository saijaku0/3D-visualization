#include "GameManager.h"

GameManager::GameManager(int width, int height) :
    isGameMode(false),
    firstMouse(true),
    escKeyPressed(false),
    lastX(static_cast<float>(width) / 2.0f),
    lastY(static_cast<float>(height) / 2.0f)
{
}

void GameManager::ToggleGameMode() {
    isGameMode = !isGameMode;
}

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

void GameManager::ProcessModeSwitch(GLFWwindow* window, FreeCamera* devCam, AttachedCamera* playerCam, GameObject* playerObj, Camera*& activeCamera) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        if (!escKeyPressed) {
            if (isGameMode) {
                switchToDeveloperMode(window, devCam, playerCam, playerObj, activeCamera);
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
        switchToGameMode(window, devCam, playerCam, activeCamera);
    }
}

/*
* Private Implementation
*/

void GameManager::switchToGameMode(GLFWwindow* window, FreeCamera* devCam, AttachedCamera* playerCam, Camera*& activeCamera) {
    if (isGameMode) return;

    isGameMode = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    syncCameraRotation(playerCam, devCam);

    activeCamera = playerCam;

    firstMouse = true;
    std::cout << "GAME MODE ACTIVATED" << std::endl;
}

void GameManager::switchToDeveloperMode(GLFWwindow* window, FreeCamera* devCam, AttachedCamera* playerCam, GameObject* playerObj, Camera*& activeCamera) {

    isGameMode = false;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glm::vec3 playerPos = playerObj->transform.Position;
    float playerScale = playerObj->transform.Scale.y;

    glm::vec3 newPos = playerPos - (playerCam->GetFront() * 2.0f * playerScale) + glm::vec3(0, 2, 0);

    devCam->SetPosition(newPos);

    syncCameraRotation(devCam, playerCam);

    activeCamera = devCam;

    std::cout << "DEVELOPER MODE ACTIVATED" << std::endl;
}

void GameManager::syncCameraRotation(Camera* dst, const Camera* src) {
    dst->SetRotation(src->GetYaw(), src->GetPitch());

    dst->ProcessMouseMovement(0, 0);
}