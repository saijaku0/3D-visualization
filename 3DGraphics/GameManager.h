#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "Player.h"
#include "IMoveAble.h"

class GameManager {
public:
    bool isGameMode;
    bool firstMouse;
    bool escKeyPressed;
    float lastX, lastY;

    GameManager(int width, int height);

    void ProcessModeSwitch(
        GLFWwindow* window,
        FreeCamera* devCam,
        AttachedCamera* playerCam,
        Player* playerObj,
        Camera** activeCamPtr,           
        IMovable** currentControllerPtr  
    );

    bool IsMouseRotationActive(GLFWwindow* window);
    

private:
    void switchToGameMode(GLFWwindow* window, FreeCamera* devCam, AttachedCamera* playerCam, Player* playerObj, Camera** activeCamPtr, IMovable** currentControllerPtr);
    void switchToDeveloperMode(GLFWwindow* window, FreeCamera* devCam, AttachedCamera* playerCam, Player* playerObj, Camera** activeCamPtr, IMovable** currentControllerPtr);
};

#endif // !GAME_MANAGER_H