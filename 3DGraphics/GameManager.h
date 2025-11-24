#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "FreeCamera.h"
#include "Player.h"
#include "IMoveAble.h"
#include "AttachedCamera.h"

class GameManager {
    bool isGameMode;
    bool firstMouse;
    bool escKeyPressed;
    float lastX, lastY;
public:

    GameManager(int width, int height);

    bool& GetGameMode() { return isGameMode; }
    bool& GetFirstMouse() { return firstMouse; }
    float& GetLastX() { return lastX; }
    float& GetLastY() { return lastY; }

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
    void switchToGameMode(
        GLFWwindow* window, 
        FreeCamera* devCam, 
        AttachedCamera* playerCam, 
        Player* playerObj, 
        Camera** activeCamPtr, 
        IMovable** currentControllerPtr
    );
    void switchToDeveloperMode(
        GLFWwindow* window, 
        FreeCamera* devCam, 
        AttachedCamera* playerCam, 
        Player* playerObj, 
        Camera** activeCamPtr, 
        IMovable** currentControllerPtr
    );
    void syncCameraRotation(Camera* dst, Camera* src);
};

#endif // !GAME_MANAGER_H