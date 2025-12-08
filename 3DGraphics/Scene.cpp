#include "Scene.h"
#include "ResourceManager.h"
#include "GeometryGenerator.h"

#include "MeshRendererComponent.h"
#include "RigidbodyComponent.h"
#include "BoxColliderComponent.h"
#include "PlayerControllerComponent.h"
#include "DebugRenderer.h"

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

void Scene::Init() {
    ResourceManager::LoadShader("shader.vert", "shader.frag", "default");
    ResourceManager::LoadShader("skybox.vert", "skybox.frag", "skybox");
    ResourceManager::StoreMesh("cube", GeometryGenerator::CreateCube());

    auto debugShader = ResourceManager::GetShader("default");
    DebugRenderer::Init(debugShader);

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
        "assets/sky_right.png", "assets/sky_left.png",
        "assets/sky_top.png",   "assets/sky_bottom.png",
        "assets/sky_front.png", "assets/sky_back.png"
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
    playerRender->mesh = ResourceManager::GetMesh("cube");
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

    // ----------------------
    // (Ground)
    // ----------------------
    auto floorObj = std::make_unique<GameObject>();
    floorObj->GetTransformPtr()->SetPosition(glm::vec3(0, -0.5f, 0));

    glm::vec3 floorScale = glm::vec3(15.0f, 1.0f, 15.0f);
    floorObj->GetTransformPtr()->SetScale(floorScale);

    auto floorRender = std::make_unique<MeshRendererComponent>(floorObj.get());
    floorRender->mesh = ResourceManager::GetMesh("cube");
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
    m_gameTime += deltaTime;

    for (auto& obj : m_gameObjects) {
        auto ctrl = obj->GetComponent<PlayerControllerComponent>();

        if (ctrl && m_gameManager.IsGameMode()) 
            ctrl->Update(deltaTime);
    }

    m_physicsWorld.Step(deltaTime);

    if (m_activeCamera) m_activeCamera->Update(deltaTime);
}

void Scene::Draw(int scrWidth, int scrHeight) {
    m_renderer.Clear();

    auto shader = ResourceManager::GetShader("default");
    glDisable(GL_CULL_FACE);

    m_renderer.DrawScene(
        *shader,
        m_activeCamera,
        m_lightingSystem,
        m_gameObjects,
        ResourceManager::GetMesh("cube"), 
        m_gameTime,
        scrWidth, scrHeight
    );

    DebugRenderer::RenderColliders(m_gameObjects, m_activeCamera);

    if (m_skybox) {
        glm::mat4 view = m_activeCamera->GetViewMatrix();
        glm::mat4 proj = m_activeCamera->GetProjectionMatrix((float)scrWidth / scrHeight);
        m_skybox->Draw(view, proj);
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