#pragma once
#ifndef SCENE_H
#define SCENE_H 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory> 

#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "FreeCamera.h"
#include "AttachedCamera.h"
#include "Player.h"
#include "LightingSystem.h"
#include "Renderer.h"
#include "GameManager.h"
#include "Skybox.h"
#include "SceneFactory.h"
#include "InputManager.h" 
#include "Ball.h"

class Scene {
    std::shared_ptr<Mesh> cubeMesh;
    std::shared_ptr<Mesh> pyramidMesh;

    std::vector<GameObject> gameObjects;
    Player playerObj;
    Ball myBall;

    Renderer renderer;
    GameManager gameManager;

    std::unique_ptr<FreeCamera> devCamera;
    std::unique_ptr<AttachedCamera> playerCamera;
    Camera* activeCamera;

    LightingSystem lightingSystem;
    Skybox* skybox;

    float gameTime;
    glm::vec3 pointLightPos;

public:
    Scene(int width, int height);
    ~Scene();

    void Init();
    void ProcessInput(GLFWwindow* window, float deltaTime);
    void ProcessMouseMovement(double xpos, double ypos, bool enableRotation);
    void Update(float deltaTime);
    void Draw(Shader& shader, int scrWidth, int scrHeight);

    GameManager& GetGameManager() { return gameManager; }

private:
    bool updateCursorState(GLFWwindow* window);
    void handleMovementInput(GLFWwindow* window, float deltaTime);
};

#endif // !SCENE_H