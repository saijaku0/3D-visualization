#include "Scene.h"
#include <imgui.h>
#include "Core/ResourceManager.h"
#include "Utils/GeometryGenerator.h"
#include "GuiManager.h"

#include "Graphics/MeshRendererComponent.h"
#include "Physics/RigidbodyComponent.h"
#include "Physics/BoxColliderComponent.h"
#include "PlayerControllerComponent.h"
#include "Physics/SphereColliderComponent.h"
#include "Graphics/DebugRenderer.h"

Scene::Scene(int width, int height, GLFWwindow* window)
    : m_gameManager(width, height),
    m_lightingSystem()
{
    m_inputManager = std::make_unique<InputManager>(window);

    Init();
}

Scene::~Scene() {
    ResourceManager::Clear();
}

unsigned int Scene::GetSceneTexture() { 
    if (!m_framebuffer) return 0;
    return m_framebuffer->GetTextureID(); 
}

void Scene::BindFramebuffer() {
    if (m_framebuffer) m_framebuffer->Bind();
}

void Scene::UnbindFramebuffer() {
    if (m_framebuffer) m_framebuffer->Unbind();
}

void Scene::Init() {
    ResourceManager::LoadShader("Engine/shader.vert", "Engine/shader.frag", "default");
    ResourceManager::LoadShader("Engine/skybox.vert", "Engine/skybox.frag", "skybox");
    ResourceManager::LoadShader("Engine/shadow_depth.vert", "Engine/shadow_depth.frag", "shadow_depth");

    ResourceManager::StoreMesh("cube", GeometryGenerator::CreateCube());
    ResourceManager::StoreMesh("sphere", GeometryGenerator::CreateSphere());

    auto debugShader = ResourceManager::GetShader("default");
    DebugRenderer::Init(debugShader);

    m_renderer.InitShadow();
    m_framebuffer = std::make_unique<Framebuffer>(800, 600);

    m_lightingSystem.dirLight.direction = glm::vec3(-0.5f, -1.0f, -0.5f);
    m_lightingSystem.dirLight.ambient = glm::vec3(0.2f);
    m_lightingSystem.dirLight.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    m_lightingSystem.dirLight.specular = glm::vec3(0.5f);

    m_lightingSystem.AddPointLight(glm::vec3(0, 3, 0), glm::vec3(1.0f, 0.8f, 0.6f));

    m_devCamera = std::make_unique<FreeCamera>(glm::vec3(0.0f, 5.0f, 10.0f));
    m_playerCamera = std::make_unique<AttachedCamera>(m_player, glm::vec3(0.0f, 2.0f, -4.0f));
    m_activeCamera = m_devCamera.get();

    CreateLevel();

    m_playerCamera->SetTarget(m_player);

    m_skybox = std::make_unique<Skybox>();
    std::vector<std::string> faces = {
        "Engine/assets/sky_right.png", "Engine/assets/sky_left.png",
        "Engine/assets/sky_top.png",   "Engine/assets/sky_bottom.png",
        "Engine/assets/sky_front.png", "Engine/assets/sky_back.png"
    };
    m_skybox->LoadCubemap(faces);
}

void Scene::CreateLevel() {
    // --- PLAYER ---
    auto playerObj = std::make_unique<GameObject>();
    playerObj->GetTransformPtr()->SetPosition(glm::vec3(1.0f, 2.0f, 1.0f));
    glm::vec3 playerScale = glm::vec3(1.0f, 2.0f, 1.0f);
    playerObj->GetTransformPtr()->SetScale(playerScale);
    auto playerRender = std::make_unique<MeshRendererComponent>(playerObj.get());
    playerRender->SetMesh(ResourceManager::GetMesh("cube"));
    playerRender->color = glm::vec3(1.0f, 0.0f, 0.0f);
    playerObj->AddComponent(std::move(playerRender));
    auto playerRb = std::make_unique<RigidbodyComponent>(playerObj.get());
    playerRb->mass = 80.0f;
    playerRb->isStatic = false;
    m_physicsWorld.AddBody(playerRb.get());
    playerObj->AddComponent(std::move(playerRb));
    auto playerCol = std::make_unique<BoxColliderComponent>(playerObj.get());
    playerCol->SetSize(playerScale);
    playerObj->AddComponent(std::move(playerCol));
    auto playerCtrl = std::make_unique<PlayerControllerComponent>(
        playerObj.get(),
        m_inputManager.get(),
        m_playerCamera.get()
    );
    playerObj->AddComponent(std::move(playerCtrl));
    m_player = playerObj.get();
    m_gameObjects.push_back(std::move(playerObj));

    /*
    * Ball
    */
    auto ballObj = std::make_unique<GameObject>();
    ballObj->GetTransformPtr()->SetPosition(glm::vec3(3.0f, 5.0f, 0.0f));
    ballObj->GetTransformPtr()->SetScale(glm::vec3(1.0f));
    auto ballRender = std::make_unique<MeshRendererComponent>(ballObj.get());
    ballRender->SetMesh(ResourceManager::GetMesh("sphere"));
    ballRender->color = glm::vec3(0.0f, 0.0f, 1.0f); 
    ballObj->AddComponent(std::move(ballRender));
    auto ballCol = std::make_unique<SphereColliderComponent>(ballObj.get());
    ballCol->radius = 0.5f;
    ballObj->AddComponent(std::move(ballCol));
    auto ballRb = std::make_unique<RigidbodyComponent>(ballObj.get());
    ballRb->mass = 10.0f; 
    ballRb->restitution = 0.8f;
    ballRb->drag = 0.5f;  
    m_physicsWorld.AddBody(ballRb.get());
    ballObj->AddComponent(std::move(ballRb));
    m_gameObjects.push_back(std::move(ballObj));

    // ----------------------
    // (Ground)
    // ----------------------
    auto floorObj = std::make_unique<GameObject>();
    floorObj->GetTransformPtr()->SetPosition(glm::vec3(0, -0.5f, 0));
    glm::vec3 floorScale = glm::vec3(55.0f, 0.5f, 55.0f);
    floorObj->GetTransformPtr()->SetScale(floorScale);
    auto floorRender = std::make_unique<MeshRendererComponent>(floorObj.get());
    floorRender->SetMesh(ResourceManager::GetMesh("cube"));
    floorRender->color = glm::vec3(0.7f, 0.7f, 0.7f);
    floorObj->AddComponent(std::move(floorRender));
    auto floorRb = std::make_unique<RigidbodyComponent>(floorObj.get());
    floorRb->isStatic = true; 
    m_physicsWorld.AddBody(floorRb.get());
    floorObj->AddComponent(std::move(floorRb));
    auto floorCol = std::make_unique<BoxColliderComponent>(floorObj.get());
    floorCol->SetSize(floorScale);
    floorObj->AddComponent(std::move(floorCol));
    m_gameObjects.push_back(std::move(floorObj));
}

void Scene::ProcessInput(GLFWwindow* window, float deltaTime) {
    m_gameManager.ProcessModeSwitch(
        window,
        m_devCamera.get(),
        m_playerCamera.get(),
        m_player,       
        m_activeCamera  
    );

    if (!m_gameManager.IsGameMode()) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_devCamera->ProcessKeyboard(CameraMovement::Forward, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_devCamera->ProcessKeyboard(CameraMovement::Backward, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            m_devCamera->ProcessKeyboard(CameraMovement::Left, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_devCamera->ProcessKeyboard(CameraMovement::Right, deltaTime);
    }
}

void Scene::Update(float deltaTime) {
    if (m_gameManager.IsGameMode()) {

        m_gameTime += deltaTime;

        for (auto& obj : m_gameObjects) {
            auto ctrl = obj->GetComponent<PlayerControllerComponent>();

            if (ctrl && m_gameManager.IsGameMode())
                ctrl->Update(deltaTime);
        }

        m_physicsWorld.Step(deltaTime);
    }

    if (m_activeCamera) m_activeCamera->Update(deltaTime);
}

void Scene::Draw(int scrWidth, int scrHeight) {
    auto mainShader = ResourceManager::GetShader("default");

    m_renderer.DrawScene(
        *mainShader,
        m_activeCamera,
        m_lightingSystem,
        m_gameObjects,
        ResourceManager::GetMesh("cube"), 
        m_gameTime,
        scrWidth, scrHeight
    );

    //DebugRenderer::RenderColliders(m_gameObjects, m_activeCamera);

    if (m_skybox) {
        glm::mat4 view = glm::mat4(glm::mat3(m_activeCamera->GetViewMatrix()));
        glm::mat4 projection = m_activeCamera->GetProjectionMatrix();
        m_skybox->Draw(view, projection);
    }
}

void Scene::ProcessMouseMovement(GLFWwindow* window, double xpos, double ypos) {
    bool enableRotation = m_gameManager.IsMouseRotationActive(window);

    if (!enableRotation) {
        m_gameManager.GetLastX() = (float)xpos;
        m_gameManager.GetLastY() = (float)ypos;
        return;
    }

    if (m_gameManager.GetFirstMouse()) {
        m_gameManager.GetLastX() = (float)xpos;
        m_gameManager.GetLastY() = (float)ypos;
        m_gameManager.GetFirstMouse() = false;
    }

    float xoffset = (float)xpos - m_gameManager.GetLastX();
    float yoffset = m_gameManager.GetLastY() - (float)ypos; 

    m_gameManager.GetLastX() = (float)xpos;
    m_gameManager.GetLastY() = (float)ypos;

    if (m_activeCamera)
        m_activeCamera->ProcessMouseMovement(xoffset, yoffset);
}

void Scene::OnResize(float width, float height) {
    if ((width == m_viewportWidth && height == m_viewportHeight) || width <= 0 || height <= 0)
        return;

    m_viewportWidth = width;
    m_viewportHeight = height;

    if (m_activeCamera) {
        m_activeCamera->SetAspectRatio(width, height);
    }

    if (m_framebuffer) {
        m_framebuffer->Rescale((int)width, (int)height);
    }
}