#pragma once
#ifndef SCENE_H
#define SCENE_H 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory> 

#include "PhysicsWorld.h"
#include "LightingSystem.h"
#include "Renderer.h"
#include "Skybox.h"
#include "FreeCamera.h"
#include "AttachedCamera.h"
#include "GameObject.h"
#include "GameManager.h"
#include "InputManager.h"

class Scene {
    PhysicsWorld m_physicsWorld;

    LightingSystem m_lightingSystem;

    Renderer m_renderer;

    std::vector<std::unique_ptr<GameObject>> m_gameObjects;

    GameObject* m_player = nullptr;

    std::unique_ptr<FreeCamera> m_devCamera;
    std::unique_ptr<AttachedCamera> m_playerCamera;
    Camera* m_activeCamera = nullptr;

    std::unique_ptr<Skybox> m_skybox;
    GameManager m_gameManager;

    float m_gameTime = 0.0f;
    std::unique_ptr<InputManager> m_inputManager;

public:
    Scene(int width, int height, GLFWwindow* window);
    ~Scene();

    void Init();

    void Update(float deltaTime);
    void Draw(int scrWidth, int scrHeight); 

    void ProcessInput(GLFWwindow* window, float deltaTime);
    void ProcessMouseMovement(GLFWwindow* window, double xpos, double ypos);

private:
    void CreateLevel();
};

#endif // !SCENE_H