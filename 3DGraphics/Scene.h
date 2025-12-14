#pragma once
#ifndef SCENE_H
#define SCENE_H 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory> 

#include "Physics/PhysicsWorld.h"
#include "Graphics/LightingSystem.h"
#include "Graphics/Renderer.h"
#include "Graphics/Skybox.h"
#include "Graphics/Framebuffer.h"
#include "Camera/FreeCamera.h"
#include "Camera/AttachedCamera.h"
#include "Core/GameObject.h"
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
    std::unique_ptr<Framebuffer> m_framebuffer;

public:
    Scene(int width, int height, GLFWwindow* window);
    ~Scene();

    void Init();

    Camera* GetActiveCamera() const { return m_activeCamera; }

    void Update(float deltaTime);
    void Draw(int scrWidth, int scrHeight); 

    void ProcessInput(GLFWwindow* window, float deltaTime);
    void ProcessMouseMovement(GLFWwindow* window, double xpos, double ypos);

    void OnResize(float width, float height);
    float GetWidth() const { return m_viewportWidth; }
    float GetHeight() const { return m_viewportHeight; }

    void BindFramebuffer();
    void UnbindFramebuffer();
    unsigned int GetSceneTexture();

private:
    void CreateLevel();

    float m_viewportWidth = 800.0f;
    float m_viewportHeight = 600.0f;
};

#endif // !SCENE_H