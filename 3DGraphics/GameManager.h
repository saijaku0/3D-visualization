#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "FreeCamera.h"
#include "AttachedCamera.h"
#include "GameObject.h" 
#include "Player.h"     

class GameManager {
    bool isGameMode;
    bool firstMouse;
    bool escKeyPressed;
    float lastX, lastY;

public:
    GameManager(int width, int height);

    // Getters
    bool IsGameMode() const { return isGameMode; } 
    bool& GetFirstMouse() { return firstMouse; }
    float& GetLastX() { return lastX; }
    float& GetLastY() { return lastY; }

    void ToggleGameMode();

    void ProcessModeSwitch(
        GLFWwindow* window,
        FreeCamera* devCam,
        AttachedCamera* playerCam,
        GameObject* playerObj, 
        Camera*& activeCamera  
    );

    bool IsMouseRotationActive(GLFWwindow* window);

private:
    void switchToGameMode(
        GLFWwindow* window,
        FreeCamera* devCam,
        AttachedCamera* playerCam,
        Camera*& activeCamera
    );

    void switchToDeveloperMode(
        GLFWwindow* window,
        FreeCamera* devCam,
        AttachedCamera* playerCam,
        GameObject* playerObj,
        Camera*& activeCamera
    );

    void syncCameraRotation(Camera* dst, const Camera* src);
};

#endif // !GAME_MANAGER_H